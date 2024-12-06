/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaeggi <chaeggi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:18:02 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/06 16:57:19 by chaeggi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

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
	init_xpm_texture(env->enjoyer, env, env->data->enjoyer);
	remove_green_bg(env->enjoyer, env);
	init_xpm_texture(env->beer_shop, env, env->data->beer_shop);
	init_xpm_texture(env->brezel_shop, env, env->data->brezel_shop);
	init_xpm_texture(env->pfandautomat, env, env->data->pfandautomat);
	init_xpm_texture(env->enj_beer, env, env->data->beer);
	remove_green_bg(env->enj_beer, env);
	init_xpm_texture(env->enj_brezel, env, env->data->brezel);
	remove_green_bg(env->enj_brezel, env);
	init_xpm_texture(env->pfand, env, env->data->pfand);
	remove_green_bg(env->pfand, env);
	init_xpm_texture(env->rules, env, env->data->rules);
	remove_green_bg(env->rules, env);
	init_xpm_texture(env->north_wall, env, env->data->north);
	init_xpm_texture(env->south_wall, env, env->data->south);
	init_xpm_texture(env->east_wall, env, env->data->east);
	init_xpm_texture(env->west_wall, env, env->data->west);
	init_xpm_texture(env->pfandbon, env, env->data->pfandbon);
	env->textures_loaded = true;
}

void	init_xpm_texture(t_img *img, t_env *env, char *path)
{
	int	height;
	int	width;

	img->img = mlx_xpm_file_to_image(env->mlx, path, &width, &height);
	if (!img->img)
		error_and_exit("Failed to load xpm image");
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
