/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:24:53 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/01 15:05:48 by mzhukova         ###   ########.fr       */
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
	init_minim_img(env->img, env);
	draw_mini_map(env);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img->img, 0, 0);
	mlx_hook(env->mlx_win, 17, 1L << 17, destroy, env);
	mlx_hook(env->mlx_win, 2, 1L << 0, key_press, env);
	mlx_hook(env->mlx_win, 3, 1L << 1, key_release, env);
	mlx_loop_hook(env->mlx, mini_draw_loop, env);
	mlx_loop(env->mlx);
}

void	init_minim_img(t_img *img, t_env *env)
{
	img->img = mlx_new_image(env->mlx, MINI_M_SIZE, MINI_M_SIZE);
	if (!img->img)
		error_and_exit("Failed to create image");
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->width, &img->endian);
	if (!img->addr)
		error_and_exit("Failed to get image data address");
}

void	draw_square(int x, int y, int size, int color, t_env *env)
{
	int	i;

	i = 0;
	while (i < size)
		my_pixel_put(x + i++, y, color, env);
	i = 0;
	while (i < size)
		my_pixel_put(x, y + i++, color, env);
	i = 0;
	while (i < size)
		my_pixel_put(x + size, y + i++, color, env);
	i = 0;
	while (i < size)
		my_pixel_put(x + i++, y + size, color, env);
}
