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
	if (!env->textures_loaded)
		put_loading_screen(env);
	init_minim_img(env->mini_map, env);
	init_texture_img(env);
	mlx_mouse_hook(env->mlx_win, mouse_hook, env);
	mlx_hook(env->mlx_win, 6, 1L << 6, mouse_move_hook, env);
	mlx_hook(env->mlx_win, 17, 1L << 17, destroy, env);
	mlx_hook(env->mlx_win, 2, 1L << 0, key_press, env);
	mlx_hook(env->mlx_win, 3, 1L << 1, key_release, env);
	mlx_loop_hook(env->mlx, mini_draw_loop, env);
	mlx_loop(env->mlx);
}

void	put_loading_screen(t_env *env)
{
	init_xpm_texture(env->loading_screen, env, env->data->loading_screen);
	if (!env->textures_loaded)
		mlx_put_image_to_window(env->mlx, env->mlx_win,
			env->loading_screen->img, 0, 0);
}

void	init_minim_img(t_img *img, t_env *env)
{
	img->img = mlx_new_image(env->mlx, MINI_M_SIZE, MINI_M_SIZE);
	if (!img->img)
		error_and_exit("Failed to create image");
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->size_line,
			&img->endian);
	if (!img->addr)
		error_and_exit("Failed to get image data address");
	img->width = MINI_M_SIZE;
	img->height = MINI_M_SIZE;
}

void	remove_green_bg(t_img *pattern_pic, t_env *env)
{
	t_img	*temp;

	temp = (t_img *)ft_malloc(sizeof(t_img));
	temp->img = mlx_new_image(env->mlx, WIDTH, HEIGHT / 2);
	if (!temp->img)
		error_and_exit("Failed to create image");
	temp->addr = mlx_get_data_addr(temp->img, &temp->bpp, &temp->size_line,
			&temp->endian);
	if (!temp->addr)
		error_and_exit("Failed to get image data address");
	temp->width = pattern_pic->width;
	temp->height = pattern_pic->height;
	put_image_to_image(pattern_pic, temp, 0, 0);
	mlx_destroy_image(env->mlx, temp->img);
	ft_free(temp);
}

void	draw_square(int size, int color, t_env *env)
{
	int	i;
	int	x;
	int	y;

	x = env->draw_x;
	y = env->draw_y;
	i = 0;
	while (i < size)
		mm_pixel_put(x + i++, y, color, env);
	i = 0;
	while (i < size)
		mm_pixel_put(x, y + i++, color, env);
	i = 0;
	while (i < size)
		mm_pixel_put(x + size, y + i++, color, env);
	i = 0;
	while (i < size)
		mm_pixel_put(x + i++, y + size, color, env);
}
