/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:24:53 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/16 14:47:21 by mzhukova         ###   ########.fr       */
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
	init_img(env->img);
	init_minimap(env->img, env->data, env);
	mlx_hook(env->mlx_win, 17, 1L << 17, destroy, env);
	mlx_key_hook(env->mlx_win, key_press, env);
	mlx_loop(env->mlx);
}
void init_minimap(t_img *img, t_data *data, t_env *env)
{
	img->img = mlx_xpm_file_to_image(env->mlx, data->pic_floor, &img->width, &img->height);
	if (!img->img)
		error_and_exit("failed to create the img");
	mlx_put_image_to_window(env->mlx, env->mlx_win, img->img, 0, 0);
	mlx_destroy_image(env->mlx, img->img);
}
void init_img(t_img *img)
{
	img->width = mini_m_h;
	img->height = mini_m_h;
	img->addr = NULL;
	img->bpp = 0;
	img->img = NULL;

}

// void	my_pixel_put(t_img *img, int x, int y, int color)
// {
// 	int	offset;

// 	offset = (img->width * y) + (x * (img->bpp / 8));

// 	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
// }

int	get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}