/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_image_handler.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 05:48:49 by tlaukat           #+#    #+#             */
/*   Updated: 2024/11/18 05:48:49 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"
#include "../Math-functions/xMath.h"

/*
#define Ceiling 0x0087CEEB
#define Floor 0x00666666
#define NO 0x00FF0000
#define SO 0x0000FF00
#define WE 0x000000FF
#define EA 0x00FFFF00*/

int	get_image_pixel(t_img *img, double x, double y)
{
	int	nx;
	int	ny;

	nx = (1 - x) * img->width;
	ny = y * img->height;
	return (*(int *)(img->addr + 4 * nx + (4 * ny * img->width)));
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_bg(t_img *frame, int i, t_env *env)
{
	int	j;

	j = 0;
	while (j < HEIGHT)
	{
		if (j < HEIGHT / 2)
			my_mlx_pixel_put(frame, i, j, env->data->floor->r * 0x10000
				+ env->data->floor->g * 0x100 + env->data->floor->b);
		else
			my_mlx_pixel_put(frame, i, j, env->data->ceiling->r * 0x10000
				+ env->data->ceiling->g * 0x100 + env->data->ceiling->b);
		j++;
	}
}

void	key_image_onto_walls(t_img *frame, t_img *image, int i, double w_pos,
		int wall_height)
{
	int		j;
	double	image_top;
	double	image_height;
	int		pixel_color;
	int		height;

	height = fmax(0, HEIGHT / 2 - wall_height / 2);
	if (height)
		image_top = 0;
	else
		image_top = (wall_height - HEIGHT) / (2.0 * wall_height);
	image_height = 1 - image_top * 2;
	j = height;
	while (j < HEIGHT - height && j < HEIGHT)
	{
		pixel_color = get_image_pixel(image, (double)w_pos - (int)w_pos, ((j
					- height) / (double)(HEIGHT - 2 * height)) * image_height
			+ image_top);
		my_mlx_pixel_put(frame, i, j, pixel_color);
		j++;
	}
}
