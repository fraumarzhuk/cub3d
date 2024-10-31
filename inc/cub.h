/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:12:38 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/31 15:12:48 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../src/Math-functions/xMath.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <string.h>
# include <math.h>
# ifdef __APPLE__
# include "../minilibx_opengl_20191021/mlx.h"
# define ESC 65307
// #  include "key_macos.h"

# elif __linux__
# include "../minilibx-linux/mlx.h"
# define ESC 65307
# endif // __linux__

//for parsing
# define N 78
# define S 83
# define E 69
# define W 87

//keys
# define WK 119
# define AK 97
# define SK 115
# define DK 100
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363
//mini map
# define mini_m_h 400
# define mini_m_w 400
# define BLOCKH 50
# define BLOCKW 50
# define mini_p 12
// # define mini_v_h ((mini_m_h / 2) / BLOCKH)
// # define mini_v_w ((mini_m_w / 2) / BLOCKW)
# define BLOCK_COL 0x0c187c9
# define MINI_BORDER_C 0x0d76d56
# define RAYCOLOR 0x0e3fd0b
# define SPEED 1
//screen size
# define WIDTH 1000
# define HEIGHT 1000


# define BPP sizeof(int32_t)
#define PI 3.14159265359


typedef struct map
{
	char		*line;
	bool		is_map;
	bool		last_line;
	struct map	*next;
	struct map	*prev;
}	t_map;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_player
{
	int		orientation;
	char	*sprite;
	double	x;
	double	y;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	rayDirX;
	double	rayDirY;
	int		xc;
	int		yc;
	float	angle;
	
	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;

	bool left_rotate;
	bool right_rotate;
}	t_player;

typedef struct s_data
{
	int		fd;
	// int		bpp;
	// char	*data; //rename??
	// int		endian;
	int		size_line;
	char	**map_copy;
	int		map_len;
	int		line_count;
	int		map_lines;
	int		true_lines;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*pic_ceiling;
	char	*pic_floor;
	t_rgb	*ceiling;
	t_rgb	*floor;
}	t_data;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		endian;
	int		width; // int size_line?
	int		height;
}	t_img;

typedef struct s_env
{
	void		*mlx;
	void		*mlx_win;
	t_data		*data;
	t_img		*img;
	t_player	*player;
}	t_env;

//parsing_file:
void	file_validation(char *argv, t_env *env);
int		parse_line(t_map **map, t_data *data);

//textures
void	save_textures(t_map *map, t_data *data);
t_rgb	*save_rgb(char *line);
void	save_floor_and_ceiling(char *line, t_data *data);
char	*get_texture(char *line, char *p_name, bool is_rgb);
void	choose_texture(char *map_line, t_data *data, int map_not_first);
void	check_rgb_num(char *str);
//add a function to test if rgbs are correct and try opening files(textures);
//maybe create a separate file for textures and rgb, for norm and readability

//parsing_map:
int		map_init(t_env *env);
void	save_map_copy(t_data *data, t_map **map);
int		is_map_line(char *line);
void	save_map_end(t_map *map);
void	save_map_lines(t_map *map, t_data *data);

//map-checks
void	map_checks(char **map_copy, t_env *env);
int		invalid_char_check(char *line, t_player *player, int y);
void	check_parsed_data(t_env *env, t_map *map);
void	check_rgb(t_data *data);
void	tabs_to_spaces(char *map_line);

//wall-checks
void	check_walls(char **map_copy, t_data *data);
void	scan_vertically(char **map_copy, t_data *data);
void	skip_h_gap(char *map_line);
int		is_wall_or_space(char c);
void	check_first_last_line(char *map_line);
int		is_map_char(char c);
void	check_vertical(char **map_copy, int y, int x);

//utils:
void	error_and_exit(char *str);
void	init_env(t_env *env);
void	init_player(t_player *player);
void	copy_spaces(char *map_line, char *new_line);

//events
int		key_press(int keycode, t_env *env);
int		key_release(int keycode, t_env *env);
int		destroy(t_env *env);

//player
void	move_player(t_player *player, t_env *env);
int		draw_loop(t_env *env);
void	clear_image(t_env *env);
bool	touch(double px, double py, t_env *env);
void	draw_triangle(int size, int x, int y, int color, t_env *env);
void	cast_ray(t_player *player, t_env *env);

//******RENDERING******//

//init window
void	init_mlx(t_env *env);
void	init_img(t_img *img, t_env *env);
int		get_color(int r, int g, int b, int a);
void	my_pixel_put(int x, int y, int color, t_env *env);
void	draw_square(int x, int y, int size, int color, t_env *env);

//minimap
void	init_minimap(t_img *img, t_data *data, t_env *env);
void	draw_map(t_env *env);
void	draw_mini_border(t_env *env);


// void create_Frame(int *Coords, ...);  //Cords=[x][y][z][x'][y'][z']
// void p_movement(char *Coords, void *key_pressed);
// void m_movement(char *Coords, void *mouse_moved);

#endif