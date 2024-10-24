/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:12:38 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/15 16:27:44 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <string.h>

# ifdef __APPLE__
# include "../minilibx_opengl_20191021/mlx.h"
# define ESC 65307
// #  include "key_macos.h"

# elif __linux__
# include "../minilibx-linux/mlx.h"
# define ESC 65307
# endif // __linux__

# define N 78
# define S 83
# define E 69
# define W 87



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

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_player
{
	t_pos	*position;
	int		orientation;
	char	*sprite;
}	t_player;

typedef struct s_data
{
	int		fd;
	char	**map_copy;
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
	int		img_width;
	int		img_height;
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
char	*get_texture(char *line, char *p_name);
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
int		invalid_char_check(char *line, t_player *player);
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
void	check_lonely_zero(char **map_copy, int x, int y);
void	check_vertical(char **map_copy, int y, int x);

//utils:
void	error_and_exit(char *str);
void	init_env(t_env *env);
void	copy_spaces(char *map_line, char *new_line);

//events
int		key_press(int keycode, t_env *env);
int		destroy(t_env *env);



//rendering
void init_mlx(t_env *env);
// void create_Frame(int *Coords, ...);  //Cords=[x][y][z][x'][y'][z']
// void p_movement(char *Coords, void *key_pressed);
// void m_movement(char *Coords, void *mouse_moved);

#endif