/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:24:53 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/12 17:56:53 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	init_mlx(t_env *env)
{
	env->mlx = mlx_init();
	if (!env->mlx)
		error_and_exit("Mlx failed");
	env->mlx_win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Cub 3D");
	if (!env->mlx_win)
		error_and_exit("Mlx failed");
	init_canvas_img(env->canvas, env);
	init_canvas_img(env->scene_canvas, env);
	init_texture_img(env);
	mlx_hook(env->mlx_win, 17, 1L << 17, destroy, env);
	mlx_hook(env->mlx_win, 2, 1L << 0, key_press, env);
	mlx_hook(env->mlx_win, 3, 1L << 1, key_release, env);
	mlx_loop_hook(env->mlx, draw_loop, env);
	mlx_loop(env->mlx);
}

void	init_texture_img(t_env *env)
{
	if (env->data->pic_floor)
		init_xpm_texture(env->floor, env, env->data->pic_floor);
	else if (env->data->floor)
		init_rgb_texture(env->floor, env->data->floor, env);
	if (env->data->pic_ceiling)
		init_xpm_texture(env->ceiling, env, env->data->pic_ceiling);
	else if (env->data->ceiling)
		init_rgb_texture(env->ceiling, env->data->ceiling, env);
	init_xpm_texture(env->north_wall, env, env->data->north);
	init_xpm_texture(env->south_wall, env, env->data->south);
	init_xpm_texture(env->east_wall, env, env->data->east);
	init_xpm_texture(env->west_wall, env, env->data->west);
}

void	init_xpm_texture(t_img *img, t_env *env, char *path)
{
	int	height;
	int	width;

	img->img = mlx_xpm_file_to_image(env->mlx, path, &width, &height);
	if (!img->img)
		error_and_exit("Failed to load floor image");
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->size_line,
		&img->endian);
	if (!img->addr)
		error_and_exit("Failed to get image data address");
	img->width = width;
	img->height = height;
}

void	init_rgb_texture(t_img *texture, t_rgb *color, t_env *env)
{
	int	m_color;
	int	y;
	int	x;

	texture->img = mlx_new_image(env->mlx, WIDTH, HEIGHT / 2);
	if (!texture->img)
		error_and_exit("Failed to create image");
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
		&texture->size_line, &texture->endian);
	if (!texture->addr)
		error_and_exit("Failed to get image data address");
	m_color = (color->r << 16) | (color->g << 8) | color->b;
	texture->width = WIDTH;
	texture->height = HEIGHT / 2;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_pixel_put(x, y, m_color, texture);
			x++;
		}
		y++;
	}
}

int	draw_loop(t_env *env)
{
	double			pos[3];
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (env->last_frame.tv_sec + (env->last_frame.tv_usec / 1e6) + 1
		/ FPS < now.tv_sec + (now.tv_usec / 1e6))
	{
		move_player(env->player, env);
		pos[0] = env->player->x / BLOCKW;
		pos[1] = 0.5;
		pos[2] = env->player->y / BLOCKH;
		make_frame(env->scene_canvas, pos, env->player->angle, env);
		render_images_on_canvas(env);
		gettimeofday(&env->last_frame, NULL);
	}
	return (1);
}
