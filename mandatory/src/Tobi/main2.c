#include "../../inc/cub.h"
#include "../Math-functions/xMath.h"

#define Window_Length 2000
#define Window_Height 1000
#define xFOV 90
#define yFOV 90
#define FOV_Mod 60
#define Render_Distance 10

#define Ceiling 0x0087CEEB
#define Floor 0x00666666
#define NO 0x00FF0000
#define SO 0x0000FF00
#define WE 0x000000FF
#define EA 0x00FFFF00

typedef struct s_imgx
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int 	width;
	int 	height;
	int		endian;
}			t_imgx;

typedef struct s_datax
{
	char	**map_copy;
	int		map_size;
	void	*mlx;
	void	*win;
	t_imgx  *ceil;
	t_imgx  *floor;
	t_imgx  *north;
	t_imgx  *south;
	t_imgx  *west;
	t_imgx  *east;
    double frame_dist;
}			t_datax;

int get_image_pixel(t_imgx *img, double x, double y)
{
	int nx;
	int ny;

	nx = x * img->width;
	ny = y * img->height;

	return(*(int*)(img->addr + 4 * nx + ( 4* ny * img->width)));
}

void	my_mlx_pixel_put(t_imgx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void put_bg(t_imgx *frame, int i, t_datax *data)
{
    int j = 0;
    while (j < Window_Height && data)
    {
        if(j < Window_Height / 2)
            my_mlx_pixel_put(frame, i, j, get_image_pixel(data->ceil,0,0));
        else
            my_mlx_pixel_put(frame, i, j, get_image_pixel(data->floor,0,0));
        j++;
    }
}

void key_image_onto_walls(t_imgx *frame, t_imgx *image, int i, double w_pos, int wall_height)
{
    int j;
    int top_y = fmax(0, Window_Height / 2 - wall_height / 2);
    int visible_height = fmin(wall_height, Window_Height - top_y);
    int pixel_color;
    j = top_y;
    // Iterate over each pixel in the wall
    while ( j < top_y + wall_height && j < Window_Height )
    {
        // Get the pixel color from the image
        pixel_color = get_image_pixel(image, (double)w_pos - (int)w_pos, ((j - top_y) / (double)visible_height));

        // Set the pixel color in the frame
        my_mlx_pixel_put(frame, i, j, pixel_color);
        j++;
    }
}

void put_wall_slice(t_imgx *frame, int i, double* pos, double *wall_pos, t_datax *data)
{
    put_bg(frame, i, data);
    //double wall_height_diff;
    if(data->frame_dist < 0)
        data->frame_dist *= -1;
    /*if (fabs(data->frame_dist) < 1e-6)  {
    wall_height_diff = 0;//(0.8 - 0.5) * (1 / data->frame_dist);
    } else {
    // Handle the case where data->frame_dist is zero
    // For example, you could set wall_height_diff to a default value
    wall_height_diff = 0;
    }*/

    double wall_height;
    if (!(fabs(data->frame_dist) < 1e-6))  {
    wall_height = (Window_Height / data->frame_dist) * (FOV_Mod / (double)yFOV * M_PI / 2.0);
    } else {
    // Handle the case where data->frame_dist is zero
    // For example, you could set wall_height to a default value
    wall_height = Window_Height;
    }
    
    
    /*int bottom_y = Window_Height / 2 + wall_height / 2;

    top_y = fmax(0, top_y - (int)(wall_height_diff * Window_Height));
    bottom_y = fmin(Window_Height, bottom_y - (int)(wall_height_diff * Window_Height));

    int color;
    color = 0x00FFFFFF;*/
    if (is_whole_t(wall_pos[0], 1e-6) && wall_pos[0] >= pos[0])
		key_image_onto_walls(frame, data->north, i, ceil(wall_pos[1]) - wall_pos[1], wall_height);
	if (is_whole_t(wall_pos[0], 1e-6) && wall_pos[0] <= pos[0])
		key_image_onto_walls(frame, data->south, i, wall_pos[1],  wall_height);
	if (is_whole_t(wall_pos[1], 1e-6) && wall_pos[1] <= pos[2])
		key_image_onto_walls(frame, data->west, i, ceil(wall_pos[0]) - wall_pos[0],  wall_height);
	if (is_whole_t(wall_pos[1], 1e-6) && wall_pos[1] >= pos[2])
		key_image_onto_walls(frame, data->east, i, wall_pos[0],  wall_height);

    /*for (int y = top_y; y < bottom_y; y++) {
        my_mlx_pixel_put(frame, i, y, color);
    }*/
}

int is_touching_wall(t_datax *data, double *pos, double *new_pos)
{
    if(new_pos[0] < 0 || new_pos[2] < 0 || new_pos[2] > data->map_size)
        return (-1);
    if(is_whole_t(new_pos[0], 1e-6))
    {
        if(data->map_copy[(int)floor(new_pos[2])][(int)round(new_pos[0])- (pos[0]>new_pos[0])] == '1')
            return (1);
    }
    if(is_whole_t(new_pos[2], 1e-6))
    {
        if(data->map_copy[(int)round(new_pos[2])- (pos[2]>new_pos[2])][(int)floor(new_pos[0])] == '1')
            return (1);
    }
    return (0);
}

void get_Wall_dist(double *pos, double dirx, double *wall_pos, t_datax *data)
{
    double new_pos[3] = {pos[0], pos[1], pos[2]};
    double dir[2] = {dirx, 0.0};
    double step;
    double distance;

    step = 0.000001;
    distance = 0;
    while (1)
    {
        to_border(new_pos, dir, new_pos);
        if (is_touching_wall(data, pos, new_pos) != 0)
            break;
        get_new_pos3(new_pos, dir, step, new_pos);
        distance = get_distance3(pos, new_pos);//sqrtf((pos[0] - new_pos[0]) * (pos[0] - new_pos[0]) + (pos[2] - new_pos[1])*(pos[2] - new_pos[1]));
        if (Render_Distance - distance < 0)
            break;
    }
    distance = get_distance3(pos, new_pos);
    data->frame_dist = distance;
    wall_pos[0] = new_pos[0];
    wall_pos[1] = new_pos[2];
}


t_imgx	Make_frame(double *pos, double dir, t_datax *data)
{
	int		i;
    double *wall_pos;
    double dirx;
	t_imgx	frame;
	
    
	frame.img = mlx_new_image(data->mlx, Window_Length, Window_Height);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bpp, &frame.line_length, &frame.endian);
	i = 0;
    wall_pos = malloc(2 * sizeof(double));
    dirx = dir - xFOV/2;
	while (i < Window_Length)
	{
        while(dirx < 0)
            dirx += 360;
        while(dirx >= 360)
            dirx -= 360;
        get_Wall_dist(pos, dirx, wall_pos, data);
        data->frame_dist *= cos(degrees_to_radians(dirx - dir)); 
        if(i % 2 == 0)
            printf( "wall_pos: %f, %f dir: %f dist: %f\n", wall_pos[0], wall_pos[1], dirx, data->frame_dist);
        put_wall_slice(&frame, i, pos, wall_pos, data);
        dirx = atan2(Window_Length/2 - (i - 0.5), (int)((Window_Length / 2) / tan(M_PI / 180 * (xFOV / 2)))) * (180.0 / M_PI) + dir;
		i++;
	}
	return (free(wall_pos), frame);
}

int	main(int argc, char **argv)
{
	double *pos;
	double dir;
	char *map_parts[] = {"111111", "100001", "100001", "100001", "111111", NULL};
	t_datax data;
	

	if (argc != 5)
		return (printf("Incorrect amount of arguments\n"), 1);
	data.map_copy = map_parts;
	data.map_size = 0;
	while (data.map_copy[data.map_size])
		data.map_size++;
	data.map_size--;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, Window_Length, Window_Height, "Cub3D");
	pos = malloc(4 * sizeof(double));
	pos[0] = strtod(argv[1], NULL);
	pos[1] = strtod(argv[2], NULL);
	pos[2] = strtod(argv[3], NULL);
	dir = strtod(argv[4], NULL);

	
	data.ceil = malloc(sizeof(t_imgx));
	data.ceil->img = mlx_xpm_file_to_image(data.mlx, "./test-textures/ceil.xpm", &data.ceil->width, &data.ceil->height);
	data.ceil->addr = mlx_get_data_addr(data.ceil->img, &data.ceil->bpp, &data.ceil->line_length, &data.ceil->endian);
	data.floor = malloc(sizeof(t_imgx));
	data.floor->img = mlx_xpm_file_to_image(data.mlx, "./test-textures/floor.xpm", &data.floor->width, &data.floor->height);
	data.floor->addr = mlx_get_data_addr(data.floor->img, &data.floor->bpp, &data.floor->line_length, &data.floor->endian);
	data.north = malloc(sizeof(t_imgx));
	data.north->img = mlx_xpm_file_to_image(data.mlx, "./test-textures/north.xpm", &data.north->width, &data.north->height);
	data.north->addr = mlx_get_data_addr(data.north->img, &data.north->bpp, &data.north->line_length, &data.north->endian);
	data.south = malloc(sizeof(t_imgx));
	data.south->img = mlx_xpm_file_to_image(data.mlx, "./test-textures/south.xpm", &data.south->width, &data.south->height);
	data.south->addr = mlx_get_data_addr(data.south->img, &data.south->bpp, &data.south->line_length, &data.south->endian);
	data.west = malloc(sizeof(t_imgx));
	data.west->img = mlx_xpm_file_to_image(data.mlx, "./test-textures/west.xpm", &data.west->width, &data.west->height);
	data.west->addr = mlx_get_data_addr(data.west->img, &data.west->bpp, &data.west->line_length, &data.west->endian);
	data.east = malloc(sizeof(t_imgx));
	data.east->img = mlx_xpm_file_to_image(data.mlx, "./test-textures/east.xpm", &data.east->width, &data.east->height);
	data.east->addr = mlx_get_data_addr(data.east->img, &data.east->bpp, &data.east->line_length, &data.east->endian);
	t_imgx frame;
	printf("Starting...\n");
	//printf("Pixel color: 0x%08X\n", get_pixel_color(pos, dir[0], dir[1], &data));
	frame = Make_frame(pos, dir, &data);
	mlx_put_image_to_window(data.mlx, data.win, frame.img, 0, 0);
	mlx_put_image_to_window(data.mlx, data.win, data.ceil->img, 10, 0);
	mlx_put_image_to_window(data.mlx, data.win, data.floor->img, 20, 0);
	mlx_put_image_to_window(data.mlx, data.win, data.north->img, 30, 0);
	mlx_put_image_to_window(data.mlx, data.win, data.south->img, 40, 0);
	mlx_put_image_to_window(data.mlx, data.win, data.west->img, 50, 0);
	mlx_put_image_to_window(data.mlx, data.win, data.east->img, 60, 0);

	printf("Done.\n");
	mlx_loop(data.mlx);
	return (0);
}