#include "../../inc/cub.h"
#include "../Math-functions/xMath.h"

#define Window_Length 2000
#define Window_Height 1000
#define xFOV 66
#define yFOV 66
#define FOV_Mod 60
#define Render_Distance 10

#define Ceiling 0x0087CEEB
#define Floor 0x00666666
#define NO 0x00FF0000
#define SO 0x0000FF00
#define WE 0x000000FF
#define EA 0x00FFFF00

typedef struct s_datax
{
	char	**map_copy;
	int		map_size;
	void	*mlx;
	void	*win;
	t_img  *ceil;
	t_img  *floor;
	t_img  *north;
	t_img  *south;
	t_img  *west;
	t_img  *east;
    double frame_dist;
}			t_datax;

int get_image_pixel(t_img *img, double x, double y)
{
	int nx;
	int ny;

	nx = x * img->width;
	ny = y * img->height;

	return(*(int*)(img->addr + 4 * nx + ( 4* ny * img->width)));
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void put_bg(t_img *frame, int i, t_env *env)
{
    int j = 0;
    while (j < Window_Height)
    {
        if(j < Window_Height / 2)
            my_mlx_pixel_put(frame, i, j, get_image_pixel(env->ceiling,0,0));
        else
            my_mlx_pixel_put(frame, i, j, get_image_pixel(env->floor,0,0));
        j++;
    }
}

void key_image_onto_walls(t_img *frame, t_img *image, int i, double w_pos, int wall_height)
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

void put_wall_slice(t_img *frame, int i, double* pos, double *wall_pos, t_env *env)
{
    put_bg(frame, i, env);
    //double wall_height_diff;
    if(env->data->frame_dist < 0)
        env->data->frame_dist *= -1;
    /*if (fabs(data->frame_dist) < 1e-6)  {
    wall_height_diff = 0;//(0.8 - 0.5) * (1 / data->frame_dist);
    } else {
    // Handle the case where data->frame_dist is zero
    // For example, you could set wall_height_diff to a default value
    wall_height_diff = 0;
    }*/

    double wall_height;
    if (!(fabs(env->data->frame_dist) < 1e-6))  {
    wall_height = (Window_Height / env->data->frame_dist) * (FOV_Mod / (double)yFOV * M_PI / 2.0);
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
		key_image_onto_walls(frame, env->north_wall, i, ceil(wall_pos[1]) - wall_pos[1], wall_height);
	if (is_whole_t(wall_pos[0], 1e-6) && wall_pos[0] <= pos[0])
		key_image_onto_walls(frame, env->south_wall, i, wall_pos[1],  wall_height);
	if (is_whole_t(wall_pos[1], 1e-6) && wall_pos[1] <= pos[2])
		key_image_onto_walls(frame, env->west_wall, i, ceil(wall_pos[0]) - wall_pos[0],  wall_height);
	if (is_whole_t(wall_pos[1], 1e-6) && wall_pos[1] >= pos[2])
		key_image_onto_walls(frame, env->east_wall, i, wall_pos[0],  wall_height);

    /*for (int y = top_y; y < bottom_y; y++) {
        my_mlx_pixel_put(frame, i, y, color);
    }*/
}

int is_touching_wall(t_data *data, double *pos, double *new_pos)
{
    if(new_pos[0] < 0 || new_pos[2] < 0 || new_pos[2] > data->true_lines)
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

void get_Wall_dist(double *pos, double dirx, double *wall_pos, t_env *env)
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
        if (is_touching_wall(env->data, pos, new_pos) != 0)
            break;
        get_new_pos3(new_pos, dir, step, new_pos);
        distance = get_distance3(pos, new_pos);//sqrtf((pos[0] - new_pos[0]) * (pos[0] - new_pos[0]) + (pos[2] - new_pos[1])*(pos[2] - new_pos[1]));
        if (Render_Distance - distance < 0)
            break;
    }
    distance = get_distance3(pos, new_pos);
    env->data->frame_dist = distance;
    wall_pos[0] = new_pos[0];
    wall_pos[1] = new_pos[2];
}


void	Make_frame(t_img *frame, double *pos, double dir, t_env *env)
{
	int		i;
    double *wall_pos;
    double dirx;
	
	i = 0;
    wall_pos = ft_malloc(2 * sizeof(double));
    dirx = dir - xFOV/2;
	while (i < Window_Length)
	{
        while(dirx < 0)
            dirx += 360;
        while(dirx >= 360)
            dirx -= 360;
        get_Wall_dist(pos, dirx, wall_pos, env);
        env->data->frame_dist *= cos(degrees_to_radians(dirx - dir)); 
        put_wall_slice(frame, i, pos, wall_pos, env);
        dirx = atan2(Window_Length/2 - (i - 0.5), (int)((Window_Length / 2) / tan(M_PI / 180 * (xFOV / 2)))) * (180.0 / M_PI) + dir;
		i++;
	}
	ft_free(wall_pos);
}
