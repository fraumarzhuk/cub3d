/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_canvas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:48:30 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/11 14:34:23 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	init_canvas_img(t_img *canvas, t_env *env)
{
	canvas->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	if (!canvas->img)
		error_and_exit("Failed to create image");
	canvas->addr = mlx_get_data_addr(canvas->img, &canvas->bpp,
			&canvas->size_line, &canvas->endian);
	if (!canvas->addr)
		error_and_exit("Failed to get image data address");
	canvas->width = WIDTH;
    canvas->height = HEIGHT;
}

void render_images_on_canvas(t_env *env)
{
	if (!env->player->render_move)
		return ;
	clear_image(env->canvas, WIDTH, HEIGHT);
	int offset_x = WIDTH - MINI_M_SIZE;
	int offset_y = HEIGHT - MINI_M_SIZE;
	put_image_to_image(env->floor, env->canvas, 0, 0);
	put_image_to_image(env->ceiling, env->canvas, 0, HEIGHT / 2);
	put_image_to_image(env->north_wall, env->canvas, 0, HEIGHT / 2);
	put_image_to_image(env->mini_map, env->canvas, offset_x, offset_y);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->canvas->img, 0, 0);
	env->player->render_move = false;
}

void put_image_to_image(t_img *src, t_img *dst, int offset_x, int offset_y)
{
	int x; 
	int y;
	char *src_pixel;
	char *dst_pixel;

	x = 0;
	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (src->addr && dst->addr && x < src->width)
		{
			src_pixel = src->addr + (y * src->size_line + x * (src->bpp / 8));
			int dst_x = x + offset_x;
			int dst_y = y + offset_y;
			if (dst_x >= 0 && dst_x < dst->width && dst_y >= 0 && dst_y < dst->height)
			{
				dst_pixel = dst->addr + (dst_y * dst->size_line + dst_x * (dst->bpp / 8));
				*(unsigned int *)dst_pixel = *(unsigned int *)src_pixel;
			}
			x++;
		}
		y++;
	}
}
