/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:24:53 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/24 17:09:39 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"


void init_mlx(t_env *env)
{
	env->mlx = mlx_init();
	if (!env->mlx)
		error_and_exit("Mlx failed");
	env->mlx_win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Cub 3D");
	if (!env->mlx_win)
		error_and_exit("Mlx failed");
	init_img(env->img, env);
	draw_map(env);
	draw_square(WIDTH / 2, HEIGHT / 2, 10, 0x00ff00, env);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img->img, 0, 0);
	mlx_hook(env->mlx_win, 17, 1L << 17, destroy, env);
	mlx_hook(env->mlx_win, 2, 1L<<0, key_press, env);
    mlx_hook(env->mlx_win, 3, 1L<<1, key_release, env);
	mlx_loop_hook(env->mlx, draw_loop, env);
	mlx_loop(env->mlx);
}

void init_img(t_img *img, t_env *env)
{
	img->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	if (!img->img)
		error_and_exit("Failed to create image");
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->width, &img->endian);
	if (!img->addr)
		error_and_exit("Failed to get image data address");
}

void	my_pixel_put(int x, int y, int color, t_env *env)
{
	int index;

	
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * env->img->width + x * (env->img->bpp / 8);
	env->img->addr[index] = color & 0xFF;
	env->img->addr[index + 1] = (color >> 8) & 0xFF;
	env->img->addr[index + 2] = (color >> 16) & 0xFF;
}


void draw_square(int x, int y, int size, int color, t_env *env)
{
	for (int i = 0; i < size; i++)
		my_pixel_put(x + i, y, color, env);
	for (int i = 0; i < size; i++)
		my_pixel_put(x, y + i, color, env);
	for (int i = 0; i < size; i++)
		my_pixel_put(x + size, y + i, color, env);
	for (int i = 0; i < size; i++)
		my_pixel_put(x + i, y + size, color, env);
}


int	get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}