/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:12:38 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/12 17:56:02 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../src/Math-functions/xMath.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# ifdef __APPLE__
#  include "../minilibx_opengl_20191021/mlx.h"
#  define ESC 53
// #  include "key_macos.h"

# elif __linux__
#  include "../minilibx-linux/mlx.h"
#  define ESC 65307
# endif // __linux__

// for parsing
# define N 78
# define S 83
# define E 69
# define W 87

// keys
# define WK 119
# define AK 97
# define SK 115
# define DK 100
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363

// mini map
# define MINI_M_SIZE 300
# define BLOCKH 50
# define BLOCKW 50
# define MINI_P 12
# define BLOCK_COL 0x0c187c9
# define MINI_BORDER_C 0x0d76d56
# define RAYCOLOR 0x0FFF9BF

// settings
# define SPEED 0.6
# define ANGLE_SPEED 2
# define NO_WC 0
# define ONLY_MVS 0
# define FPS 60

// screen size
# define WIDTH 1000
# define HEIGHT 1000

// walls
# define TILE_S 50

// raycasting
# define X_FOV 60
# define Y_FOV 60
# define FOV_MOD 60
# define RENDER_DISTANCE 100

# define PI 3.14159265359

typedef struct map
{
	char			*line;
	bool			is_map;
	bool			last_line;
	struct map		*next;
	struct map		*prev;
}					t_map;

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct s_player
{
	int				orientation;
	char			*sprite;
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				xc;
	int				yc;
	float			angle;
	int				mm_p_height;
	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;
	bool			left_rotate;
	bool			right_rotate;
	bool			render_move;
	int				counter;
}					t_player;

typedef struct s_data
{
	int				fd;
	int				size_line;
	char			**map_copy;
	double			frame_dist;
	int				map_len;
	int				line_count;
	int				map_lines;
	int				true_lines;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*pic_ceiling;
	char			*pic_floor;
	t_rgb			*ceiling;
	t_rgb			*floor;
}					t_data;

typedef struct s_img
{
	void			*img;
	char			*addr;
	char			*data;
	int				bpp;
	int				endian;
	int				size_line;
	int				width;
	int				height;
	char			*src_pixel;
	char			*dst_pixel;
}					t_img;

typedef struct s_env
{
	void			*mlx;
	void			*mlx_win;
	struct timeval	last_frame;
	t_data			*data;
	t_img			*canvas;
	t_img			*scene_canvas;
	t_img			*mini_map;
	t_img			*floor;
	t_img			*ceiling;
	t_img			*north_wall;
	t_img			*south_wall;
	t_img			*east_wall;
	t_img			*west_wall;
	t_player		*player;
}					t_env;

typedef struct s_raycast
{
	double			pos[3];
	double			dirx;
	double			wall_pos[3];
	double			new_pos[3];
	double			dir[2];
	double			frame_dist;
	double			wall_height;
	int				i;
}					t_raycast;

//******PARSING******//

// map_checks
void				map_checks(char **map_copy, t_env *env);
int					invalid_char_check(char *line, t_player *player, int y);
void				check_first_last_line(char *map_line);
void				check_rgb(t_data *data);

// parsing_file:
void				file_validation(char *argv, t_env *env);
int					parse_line(t_map **map, t_data *data);
void				set_player_pos(t_player *player, int x, int y, char orient);

// parsing_map:
int					map_init(t_env *env);
void				save_map_end(t_map *map);
int					is_map_line(char *line);
void				save_map_copy(t_data *data, t_map **map);
void				save_map_lines(t_map *map, t_data *data);

// parsing_utils
int					is_wall_or_space(char c);
int					is_map_char(char c);
void				tabs_to_spaces(char *map_line);
void				check_rgb_num(char *str);

// textures
void				save_textures(t_map *map, t_data *data);
void				choose_texture(char *map_line, t_data *data,
						int map_not_first);
char				*get_texture(char *line, char *p_name, bool is_rgb);
void				save_floor_and_ceiling(char *line, t_data *data);
t_rgb				*save_rgb(char *line);

// wall-checks
void				check_walls(char **map_copy, t_data *data);
void				scan_vertically(char **map_copy, t_data *data);
void				skip_h_gap(char *map_line);
void				check_vertical(char **map_copy, int y, int x);

// utils:
void				error_and_exit(char *str);
void				init_env(t_env *env);
void				init_player(t_player *player);
void				copy_spaces(char *map_line, char *new_line);
void				init_textures(t_env *env);

//******RENDERING******//

// events
int					key_press(int keycode, t_env *env);
int					key_release(int keycode, t_env *env);
int					destroy(t_env *env);

// init_canvas
void				init_canvas_img(t_img *canvas, t_env *env);
void				render_images_on_canvas(t_env *env);

// init window
void				init_mlx(t_env *env);
void				init_texture_img(t_env *env);
void				init_xpm_texture(t_img *img, t_env *env, char *path);
void				init_rgb_texture(t_img *texture, t_rgb *color, t_env *env);
int					draw_loop(t_env *env);

// player
float				new_angle(float angle, float angle_speed, bool left,
						bool right);
void				move_player(t_player *player, t_env *env);
void				set_new_coords(t_player *player, double next_x,
						double next_y);

// raycasting_image_handler
int					get_image_pixel(t_img *img, double x, double y);
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
void				put_bg(t_img *frame, int i, t_env *env);
void				img_to_wall(t_img *frame, t_img *image, t_raycast *rc,
						double w_pos);

// raycasting
void				set_raycast(t_raycast *rc, double *pos);
void				put_wall_slice(t_img *frame, t_raycast *rc, t_env *env);
int					is_touching_wall(t_data *data, double *pos,
						double *new_pos);
int					get_wall_dist(t_raycast *rc, t_env *env);
void				make_frame(t_img *frame, double *pos, double dir,
						t_env *env);

// render_utils
int					get_color(int r, int g, int b, int a);
void				mm_pixel_put(int x, int y, int color, t_env *env);
void				my_pixel_put(int x, int y, int color, t_img *img);
void				clear_image(t_img *img, int width, int height);

#endif