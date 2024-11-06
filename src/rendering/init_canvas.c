/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_canvas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:48:30 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/06 17:45:20 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	init_canvas_img(t_img *canvas, t_env *env)
{
	canvas->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	if (!canvas->img)
		error_and_exit("Failed to create image");
	canvas->addr = mlx_get_data_addr(canvas->img, &canvas->bpp,
			&canvas->width, &canvas->endian);
	if (!canvas->addr)
		error_and_exit("Failed to get image data address");
	//kurwa_check_canvas(canvas);
}

void render_minimap_on_canvas(t_env *env)
{

	//clear_image(env->canvas);
	int offset_x = WIDTH - MINI_M_SIZE;
	int offset_y = HEIGHT - MINI_M_SIZE;
	put_image_to_image(env->mini_map, env->canvas, offset_x, offset_y);
}

void put_image_to_image(t_img *src, t_img *dst, int offset_x, int offset_y)
{
	int x, y;
	char *src_pixel;
	char *dst_pixel;

	printf("src_height: %d, width:  %d\n", src->height, src->width);
	printf("DST_height: %d, width:  %d\n", dst->height, dst->width);
	for (y = 0; y < src->height; y++)
	{
		for (x = 0; x < src->width; x++)
		{
			src_pixel = src->addr + (y * src->width + x * (src->bpp / 8));
			dst_pixel = dst->addr + ((y + offset_y) * dst->width + (x + offset_x) * (dst->bpp / 8));
			*(unsigned int *)dst_pixel = *(unsigned int *)src_pixel;
		}
	}
}