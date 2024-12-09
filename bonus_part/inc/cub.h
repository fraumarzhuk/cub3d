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
# define BK 98
# define MK 109
# define UP 65362
# define PK 112
# define XK 120
# define EK 101
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363
# define SPACE 32
# define HK 104
// mouse
# define MOUSE_SENS 0.1
// mini map
# define MINI_M_SIZE 200
# define BLOCKH 20
# define BLOCKW 20
# define MINI_P 6
# define BLOCK_COL 0x0c187c9
# define A_BLOCK_COL 0x09ABF80
# define BS_BLOCK_COL 0x0AB4459
# define MS_BLOCK_COL 0x0F29F58
# define MINI_BORDER_C 0x0d76d56
# define RAYCOLOR 0x0FFF9BF
# define SPEED 2
# define ANGLE_SPEED 2
// screen size
# define WIDTH 1000
# define HEIGHT 1000

// walls
# define TILE_S 50

// raycasting
# define X_FOV 60
# define Y_FOV 60
# define FOV_MOD 60
# define RENDER_DISTANCE 1000
# define REACH_DISTANCE 1
# define Object_Width 0.1
# define Object_Min_dist 0.4 

# define PI 3.14159265359

// player
# define SLIDING_SPEED 0.1
# define HANDS 1
# define BEER 2
# define BREZEL 3

// game
# define SHOP_BEER 1
# define SHOP_BREZEL 1
# define BEER_SPRINT 1
# define SPEED_ADD 0.3
# define BREZEL_WIN 1

// UI
# define UI_TEXT 0
# define UI_HEIGHT 200
# define UI_BACKGROUND_C 0x0c187c9
# define UI_BORDER_C 0x0d76d56
# define UI_TEXT_C 0x0FFF9BF
# define HIDEPLAYER 0

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
	int				p_x;
	int				p_y;
	int 			touches_h_wall;
	int				touches_v_wall;
	bool 			no_rotate;
	int				xc;
	int				yc;
	float			angle;
	int				mm_p_height;
	double			pfand_sum;
	bool			mouse_on;
	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;
	bool			left_rotate;
	bool			right_rotate;
	bool			render_move;
	bool			display_bon;
	bool			display_rules;
	int				player_pos;
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
	int				pfand_amount;
	int				pfand_collected;
	char			looking_at;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*pic_ceiling;
	char			*pic_floor;
	char			*enjoyer;
	char			*beer;
	char			*brezel;
	char			*beer_shop;
	char			*brezel_shop;
	char			*pfand;
	char			*pfandautomat;
	char			*loading_screen;
	char			*pfandbon;
	char			*rules;
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
	bool 			textures_loaded;
	int				draw_x;
	int				draw_y;
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
	t_img			*enjoyer;
	t_img			*enj_beer;
	t_img			*enj_brezel;
	t_img			*brezel_shop;
	t_img			*beer_shop;
	t_img			*pfand;
	t_img			*pfandautomat;
	t_img			*loading_screen;
	t_img			*pfandbon;
	t_img			*rules;
	t_img			*screen_shot;
	t_player		*player;
}					t_env;

typedef struct s_object
{
	struct s_object	*next;
	double			dist;
	double			pos;
}					t_object;

typedef struct s_raycast
{
	double			pos[3];
	double			dirx;
	double			wall_pos[3];
	double			f_w_pos;
	double			new_pos[3];
	double			dir[2];
	double			frame_dist;
	double			wall_height;
	char			facing;
	char			wall_char;
	t_img			*wall_image;
	t_object		*pfand;
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
int					is_wall_mm(char c);
int					is_map_char(char c);
void				tabs_to_spaces(char *map_line);
void				check_rgb_num(char *str);

//pfand_collect
void				find_pfandamount(t_data *data);
void				collect_pfand(t_env *env);
void				give_pfand_to_automat(t_env *env);
void				display_pfandbon(t_env *env);
int					is_pfand_around(int x, int y, char **map, t_player *player);

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
void				save_wall_textures(char *map_line, t_data *data);

// utils:
void				error_and_exit(char *str);
void				init_env(t_env *env);
void				init_player(t_player *player);
void				copy_spaces(char *map_line, char *new_line);
void				init_textures(t_env *env);

//******RENDERING******//

// events
int					key_press(int keycode, t_env *env);
void				toggle_pictures(int keycode, t_env *env);
int					key_release(int keycode, t_env *env);
void 				win(t_env *env);
int					destroy(t_env *env);

// mouse
void				rotate_with_mouse(t_env *env, int x, int y);
int					mouse_hook(int button, int x, int y, t_env *env);
int					mouse_move_hook(int x, int y, t_env *env);

// init_canvas
void				init_canvas_img(t_img *canvas, t_env *env);
void				render_images_on_canvas(t_env *env);
void				display_player_pos(t_env *env);
void				put_image_to_image(t_img *src, t_img *dst, int offset_x,
						int offset_y);
int					is_correct_pixel(t_img *dst, char *src_pixel, int offs_x, int offs_y);

// init window
void				init_mlx(t_env *env);
void				init_minim_img(t_img *img, t_env *env);
void				put_loading_screen(t_env *env);
void				draw_square(int size, int color, t_env *env);
void				remove_green_bg(t_img *pattern_pic, t_env *env);

//init_textures
void				init_texture_img(t_env *env);
void				init_nobg_texture_img(t_env *env);
void				init_xpm_texture(t_img *img, t_env *env, char *path);
void				init_rgb_texture(t_img *texture, t_rgb *color, t_env *env);

// mini_map
int					mini_draw_loop(t_env *env);
void				draw_mini_map(t_env *env);
void				calculate_draw_xy(t_env *env, int y, double px_offset,
						double py_offset);
void				draw_mini_border(t_env *env);

// mini_raycasting
bool				touch(double px, double py, t_env *env);
void				cast_mini_ray(t_player *player, t_env *env);
void				draw_line(double px, double py, float angle, t_env *env);

// player
void 				wall_slide(t_player *player, t_env *env, double next_x, double next_y);
float				new_angle(float angle, float angle_speed, bool left,
						bool right);
void				move_player(t_player *player, t_env *env);
void				move_player(t_player *player, t_env *env);
void				set_new_coords(t_env *env, double next_x, double next_y);
void				draw_triangle(int size, int x, int y, int color,
						t_env *env);

// raycasting_image_handler
void				put_bg_slice(t_img *frame, int i, double dir, t_env *env);
int					get_image_pixel(t_img *img, double x, double y);
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
void				put_bg(t_img *frame, int i, t_env *env);
void				img_to_wall(t_img *frame, t_img *image, t_raycast *rc);

// raycasting objects
void				find_intersection(t_raycast *rc, double *obj, double *intersect);
void				check_objects(t_raycast *rc);
void				print_object_slice(t_img *frame, t_raycast *rc, t_env *env);
void				next_object(t_raycast *rc);

void				init_data(t_data *data);
void				ft_free_images(t_env *env);

// raycasting_utils
int					is_wall(char c, t_raycast *rc);
t_img				*get_wall_img(t_env *env, t_raycast *rc);
char				get_facing(t_raycast *rc);

// raycasting
void				set_raycast(t_raycast *rc, double *pos);
void				put_wall_slice(t_img *frame, t_raycast *rc, t_env *env);
int					is_touching_wall(t_raycast *rc, t_data *data, double *pos,
						double *new_pos);
int					get_wall_dist(t_raycast *rc, t_env *env);
void				make_frame(t_img *frame, double *pos, double dir,
						t_env *env);

// render_utils
void				mm_pixel_put(int x, int y, int color, t_env *env);
void				my_pixel_put(int x, int y, int color, t_img *img);
int					get_color(int r, int g, int b, int a);
void				clear_image(t_img *img, int width, int height);
void 				get_screenshot_image(t_env *env);

// shops
int					filter_events(int keycode, t_env *env);
void				handle_shop_events(int keycode, t_env *env);

// ui
void				draw_ui(t_env *env, t_img *canvas, int mode);

// Xmlx
void				grab_mouse(void *xvar, void *win);
void				ungrab_mouse(void *xvar);
unsigned int		get_screen_color(void *xvar, void *win, int x, int y);
void				draw_filled_square(int size, int color, t_env *env);
void				draw_mini_map_walls(t_env *env, char position);
#endif