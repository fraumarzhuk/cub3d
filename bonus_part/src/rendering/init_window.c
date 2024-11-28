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
	//printf("3\n");
	init_xpm_texture(env->enjoyer, env, env->data->enjoyer);
	//printf("2\n");
	init_xpm_texture(env->beer_shop, env, env->data->beer_shop);
	//printf("1\n");
	// init_xpm_texture(env->enj_beer, env, env->data->beer);
	remove_green_bg(env->enjoyer, env);
	//printf("0\n");
	init_xpm_texture(env->enj_brezel, env, env->data->brezel);
	// here will be all of the other images
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
	for (int y = 0; y < HEIGHT / 2; y++)
	{
		for (int x = 0; x < WIDTH; x++)
			my_pixel_put(x, y, m_color, texture);
	}
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
	ft_free(temp);
}

void	draw_square(int x, int y, int size, int color, t_env *env)
{
	int	i;

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
