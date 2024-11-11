#include "../../inc/cub.h"
#include "../Math-functions/xMath.h"

#define Window_Length 2000
#define Window_Height 1000
#define xFOV 60
#define yFOV 60
// IW = Initial Window (Camera)
#define IW_Height 0.05
#define IW_Length 0.05

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
}			t_datax;

typedef struct s_imgx
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}			t_imgx;

int	grab_pixel_color(double *w_pos, t_datax *data, int negative)
{
	if (w_pos[1] == 0)
		return (Floor);
	if (w_pos[1] == 1)
		return (Ceiling);
	if (is_whole_t(w_pos[0], 1e-5) && negative)
		return (NO);
	if (is_whole_t(w_pos[0], 1e-5) && !negative)
		return (SO);
	if (is_whole_t(w_pos[2], 1e-5) && negative)
		return (WE);
	if (is_whole_t(w_pos[2], 1e-5) && !negative)
		return (EA);
	/*printf("w_pos[2] = %f\n", w_pos[2]);
	int result = is_whole_t(w_pos[2], 0.00001);
	printf("result = %d\n", result);*/
	
	if (!data)
		return (0x00000000);
	printf("Error: w_pos: (%f, %f, %f), Test: %d \n", w_pos[0], w_pos[1], w_pos[2], (double)(int)w_pos[2]==w_pos[2]);
	if((((int)floor(10 * w_pos[0])%2) + ((int)floor(10 * w_pos[1])%2) + ((int)floor(10 * w_pos[2])%2)) % 2 == 0)
		return(0x00FF55BB);
	return (0x00000000);
}

int	is_wall_negative(double dirx, double diry, double *w_pos)
{
	if (is_whole(w_pos[0])) // x
	{
		if (dirx >= 90 && dirx < 270)
			return (!(diry >=270 || diry <= 90));
	}
	if (is_whole(w_pos[2])) // z
	{
		if (dirx >= 0 && dirx < 180)
			return (!(diry >=270 || diry <= 90));
	}
	if (is_whole(w_pos[1])) // y
		return (0);
	return (1);
}

int	is_touching_wall(t_datax *data, double *pos)
{
	double	x;
	double	z;

	x = pos[0];
	z = pos[2];
	// printf("x: %f, z: %f\n", x, z);
	if (z >= data->map_size || z < 1)
		return (-1);
	if (ft_strlen(data->map_copy[(int)floor(z)]) < floor(x) + 1 || x < 0)
		return (-1);
	if (is_whole(x))
	{
		if (data->map_copy[(int)floor(z)][(int)x] == '1'
			|| data->map_copy[(int)ceil(z)][(int)x] == '1')
			return (1);
	}
	else if (is_whole(z))
	{
		if (data->map_copy[(int)z][(int)floor(x)] == '1'
			|| data->map_copy[(int)z][(int)ceil(x)] == '1')
			return (1);
	}
	return (0);
}

void	get_wall_pos(double *pos, double dirx, double diry, t_datax *data,
		double *w_pos)
{
	double	*new_pos;
	double	dir[2];
	double	step;

	new_pos = malloc(4 * sizeof(double));
	new_pos[0] = pos[0];
	new_pos[1] = pos[1];
	new_pos[2] = pos[2];
	dir[0] = dirx;
	dir[1] = diry;
	step = 0.001;
	while (1)
	{
		to_border(new_pos, dir, w_pos);
		if (is_touching_wall(data, w_pos) != 0 || is_whole(w_pos[1]))
			break ;
		else
			get_new_pos3(new_pos, dir, step, new_pos);
	}
	free(new_pos);
}

double three_sixty_fit(double degrees)
{
	while (degrees > 360)
		degrees -= 360;
	while (degrees < 0)
		degrees += 360;
	return (degrees);
}

int	get_pixel_color(double *pos, double dirx, double diry, t_datax *data)
{
	double	*w_pos;
	int		negative;
	int		color;

	dirx = three_sixty_fit(dirx);
	diry = three_sixty_fit(diry);
	w_pos = malloc(4 * sizeof(double));
	get_wall_pos(pos, dirx, diry, data, w_pos);
	negative = is_wall_negative(dirx, diry, w_pos);
	color = grab_pixel_color(w_pos, data, negative);
	free(w_pos);
	return (color);
}

void	new_pos(double *pos, double *dir, double distx, double disty)
{
	double rad_dirx = degrees_to_radians(dir[0]); 
    double rad_diry = degrees_to_radians(dir[1]); 
	// Calculate the horizontal movement
    pos[0] += distx * cos(rad_dirx);
    pos[2] += distx * sin(rad_dirx);

    // Calculate the vertical movement
    pos[0] += disty * cos(rad_dirx) * sin(rad_diry);
    pos[1] += disty * cos(rad_diry);
    pos[2] += disty * sin(rad_dirx) * sin(rad_diry);
}

void	my_mlx_pixel_put(t_imgx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

t_imgx	Make_frame(double *pos, double *dir, t_datax *data)
{
	int		i;
	int		j;
	double	dirx;
	double	diry;
	t_imgx	frame;

	new_pos(pos, dir, -(IW_Length / 2), -(IW_Height / 2));
	dirx = dir[0] - (xFOV / 2);
	diry = dir[1] + (yFOV / 2);
	frame.img = mlx_new_image(data->mlx, Window_Length, Window_Height);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bpp, &frame.line_length,
		&frame.endian);
	j = 0;
	while (j < Window_Height)
	{
		i = 0;
		while (i < Window_Length)
		{
			new_pos(pos, dir, (IW_Length / Window_Length), 0);
			//printf("Creating pixel: %d: x:%f y:%f z:%f, dir: %f, %f\n", i + Window_Length * (j + 1), pos[0], pos[1], pos[2], dirx + i * (xFOV/(double) Window_Length), diry + j * ((double)yFOV / Window_Height));
			my_mlx_pixel_put(&frame, i, j, get_pixel_color(pos, dirx + i * (xFOV/(double) Window_Length), diry - j *  (yFOV/(double) Window_Height), data));
			// dirx + i * (xFOV/ Window_Length), diry + j * (yFOV
			// / Window_Height),
			i++;
		}
		new_pos(pos, dir, -IW_Length, (IW_Height / Window_Height)); //(IW_Height / Window_Height));
		j++;
	}
	return (frame);
	/*double xdirection_step;
	xdirection_step = xFOV / Window_Length;
	ydirection_step = yFOV / Window_Height;
	dir [0] = dir[0] - (xFOV / 2);
	dir [1] = dir[1] - (yFOV / 2);
	pos*/
	/*double direction_step = FOV / Window_Length;
	current_direction = dir[0] - (FOV / 2);
	for (int i = 0; i < Window_Length; i++)
	{
		position_step = Window_Height / 2;
		for (int j = 0; j < Window_Height; j++)
		{
			current_pos[0] = pos[0];
			current_pos[1] = pos[1];
			current_pos[2] = pos[2];
			direction_offset = current_direction - dir[1];
			current_pos[0] += direction_offset * some_factor;
			current_pos[1] += direction_offset * some_factor;
			get_pixel_color(current_pos, dir, &map, data);
			current_direction += direction_step;
		}
	}*/
}

int	main(int argc, char **argv)
{
	double *pos;
	double *dir;
	char *map_parts[] = {"111", "101", "111", NULL};
	t_datax data;

	if (argc != 6)
		return (printf("Incorrect amount of arguments\n"), 1);
	data.map_copy = map_parts;
	data.map_size = 0;
	while (data.map_copy[data.map_size])
		data.map_size++;
	data.map_size--;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, Window_Length, Window_Height, "Cub3D");
	pos = malloc(4 * sizeof(double));
	dir = malloc(3 * sizeof(double));
	pos[0] = strtod(argv[1], NULL);
	pos[1] = strtod(argv[2], NULL);
	pos[2] = strtod(argv[3], NULL);
	dir[0] = strtod(argv[4], NULL);
	dir[1] = strtod(argv[5], NULL);
	t_imgx frame;
	printf("Starting...\n");
	//printf("Pixel color: 0x%08X\n", get_pixel_color(pos, dir[0], dir[1], &data));
	frame = Make_frame(pos, dir, &data);
	mlx_put_image_to_window(data.mlx, data.win, frame.img, 0, 0);
	printf("Done.\n");
	mlx_loop(data.mlx);
	return (0);
}