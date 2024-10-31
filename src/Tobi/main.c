#include "../../inc/cub.h"
#include "../Math-functions/xMath.h"

#define Window_Length 1920
#define Window_Height 1080
#define xFOV 60
#define yFOV 60
// IW = Initial Window (Camera)
#define IW_Height 0.1
#define IW_Length 0.1

#define Ceiling 0x007777FF
#define Floor 0x00666666
#define NO 0x00FF0000
#define SO 0x0000FF00
#define WE 0x000000FF
#define EA 0x00FFFF00

typedef struct s_datax
{
	char	**map_copy;
	void	*mlx;
	void	*win;
}			t_datax;

int	grab_pixel_color(double *w_pos, t_datax *data, int negative)
{
	if (w_pos[1] == 0)
		return (Floor);
	if (w_pos[1] == 1)
		return (Ceiling);
	if (is_whole(w_pos[0]) && negative)
		return (NO);
	if (is_whole(w_pos[2]) && negative)
		return (SO);
	if (is_whole(w_pos[0]) && !negative)
		return (WE);
	if (is_whole(w_pos[2]) && !negative)
		return (EA);
	return (0x00000000);
}

int	is_wall_negative(double dirx, double *w_pos)
{
	if (is_whole(w_pos[0])) // x
	{
		if (dirx >= 0 && <= 180)
			return (0);
	}
	if (is_whole(w_pos[2])) // z
	{
		if (dirx >= 90 && <= 270)
			return (0);
	}
	if (is_whole(w_pos[1])) // y
		return (0);
	return (1);
}

void	get_wall_pos(double *pos, double dirx, double diry, char **map,
		double *w_pos)
{
	double	*new_pos;
	double	dir[2];
	double	step;

	new_pos = ft_malloc(4 * sizeof(double));
	new_pos[0] = pos[0];
	new_pos[1] = pos[1];
	new_pos[2] = pos[2];
	dir[0] = dirx;
	dir[1] = diry;
	step = 0.01;
	while (1)
	{
		to_border(new_pos, dir, w_pos);
		if (map[(int)w_pos[0]][(int)w_pos[2]] == 1 || is_whole(w_pos[1]))
			break ;
		else
			get_new_pos3(new_pos, dir, step, new_pos);
	}
	free(new_pos);
}

int	get_pixel_color(double *pos, double dirx, double diry, t_datax *data)
{
	double	*w_pos;
	int		negative;
	int		color;

	w_pos = ft_malloc(4 * sizeof(double));
	get_wall_pos(pos, dirx, diry, t_datax->map_copy, w_pos);
	negative = is_wall_negative(dirx, w_pos);
	color = grab_pixel_color(w_pos, data, negative);
	free(w_pos);
}

void	new_pos(double *pos, double *dir, double distx, double disty)
{
	dir[0] = dir[0] + 90 * (0 <= distx) - 90 * (0 > distx);
	get_new_pos3(pos, dir, distx, pos);
	dir[0] = dir[0] - 90 * (0 <= distx) + 90 * (0 > distx);
	dir[1] = dir[1] + 90 * (0 <= disty) - 90 * (0 > disty);
	get_new_pos3(pos, dir, disty, pos);
	dir[1] = dir[1] - 90 * (0 <= disty) + 90 * (0 > disty);
}

void	my_mlx_pixel_put(t_datax *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_img	Make_frame(double *pos, double *dir, t_datax *data)
{
	int		i;
	int		j;
	int		dirx;
	int		diry;
	t_img	frame;
	double	ydirection_step;
	double	current_direction;
		double current_pos[3];
	double	position_step;
	double	direction_offset;

	new_pos(pos, dir, -(IW_Length / 2), -(IW_Height / 2));
	dirx = dir[0] - (xFOV / 2);
	diry = dir[1] - (yFOV / 2);
	frame.img = mlx_new_image(data->mlx, Window_Length, Window_Height);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bpp, &frame.size_line,
		&frame.endian);
	j = 0;
	while (j < Window_Height)
	{
		i = 0;
		while (i < Window_Length)
		{
			new_pos(pos, dir, (IW_Length / Window_Length), 0);
			my_mlx_pixel_put(&frame, i, j, get_pixel_color(pos, dirx + i * (xFOV
						/ Window_Length), diry + j * (yFOV / Window_Height),
					map, data));
			i++;
		}
		new_pos(pos, dir, -IW_Length, (IW_Height / Window_Height));
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
	int *pos;
	int *dir;
	char *map_parts[] = {"111111111111111111111111111111111",
		"111111111000000000110000000000001",
		"111111111011000001110000000000001",
		"111111111001000000000000000000001",
		"111111111011000001110000000000001",
		"100000000011000001110111111111111", "11110111111111011100000010001",
		"11110111111111011101010010001", "11000000110101011100000010001",
		"10000000000000001100000010001", "10000000000000001101010010001",
		"11000001110101011111011110N0111", "11110111 1110101 101111010001",
		"11111111 1111111 111111111111"};
	t_datax data;

	if (argc != 6)
		return (printf("Incorrect amount of arguments\n"), 1);
	data.map_copy = map_parts;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, Window_Length, Window_Height, "Cub3D");
	pos = malloc(4 * sizeof(int));
	dir = malloc(3 * sizeof(int));
	pos[0] = strtod(argv[1], NULL);
	pos[1] = strtod(argv[2], NULL);
	pos[2] = strtod(argv[3], NULL);
	dir[0] = strtod(argv[4], NULL);
	dir[1] = strtod(argv[5], NULL);
	t_img frame;
	frame = Make_frame(double *pos, double *dir, t_datax *data);
	mlx_put_image_to_window(data.mlx, data.win, frame.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}