/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:59:06 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/06 17:28:06 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	mm_pixel_put(int x, int y, int color, t_env *env)
{
	int	index;

	if (x >= MINI_M_SIZE || y >= MINI_M_SIZE || x < 0 || y < 0)
		return ;
	index = y * env->mini_map->width + x * (env->mini_map->bpp / 8);
	env->mini_map->addr[index] = color & 0xFF;
	env->mini_map->addr[index + 1] = (color >> 8) & 0xFF;
	env->mini_map->addr[index + 2] = (color >> 16) & 0xFF;
}

void my_pixel_put(int x, int y, int color, t_img *img)
{
    char *dst;

	if (x <= WIDTH && y <= HEIGHT && x > 0 && y > 0)
    {
        dst = img->addr + (y * img->width + x * (img->bpp / 8));
        *(unsigned int *)dst = color;
    }
	//int	index;

	// if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
	// 	return ;
	// index = y * img->width + x * (img->bpp / 8);
	// img->addr[index] = color & 0xFF;
	// img->addr[index + 1] = (color >> 8) & 0xFF;
	// img->addr[index + 2] = (color >> 16) & 0xFF;
}

int	get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	clear_image(t_img *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_pixel_put(x, y, RAYCOLOR, img);
			x++;
		}
		y++;
	}
}

void	clear_mm_image(t_img *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < MINI_M_SIZE/ 2)
	{
		x = 0;
		while (x < MINI_M_SIZE /2)
		{
			my_pixel_put(x, y, RAYCOLOR, img);
			x++;
		}
		y++;
	}
}

void	kurwa_check_canvas(t_img *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_pixel_put(x, y, MINI_BORDER_C, img);
			x++;
		}
		y++;
	}
}