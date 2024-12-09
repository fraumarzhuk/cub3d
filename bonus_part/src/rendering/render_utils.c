/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:59:06 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/09 05:16:30 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	mm_pixel_put(int x, int y, int color, t_env *env)
{
	int	index;

	if (x >= MINI_M_SIZE || y >= MINI_M_SIZE || x < 0 || y < 0)
		return ;
	index = y * env->mini_map->size_line + x * (env->mini_map->bpp / 8);
	env->mini_map->addr[index] = color & 0xFF;
	env->mini_map->addr[index + 1] = (color >> 8) & 0xFF;
	env->mini_map->addr[index + 2] = (color >> 16) & 0xFF;
}

void	my_pixel_put(int x, int y, int color, t_img *img)
{
	char	*dst;

	if (x <= WIDTH && y <= HEIGHT && x > 0 && y > 0)
	{
		dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	clear_image(t_img *img, int width, int height)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			my_pixel_put(x, y, 0, img);
			x++;
		}
		y++;
	}
}

void	get_screenshot_image(t_env *env)
{
	static int	i;
	int			x;
	int			y;

	i = 0;
	y = 1;
	if (i == 0)
	{
		env->screen_shot = (t_img *)ft_malloc(sizeof(t_img));
		env->screen_shot->img = mlx_new_image(env->mlx, WIDTH - MINI_M_SIZE,
			UI_HEIGHT);
		env->screen_shot->addr = mlx_get_data_addr(env->screen_shot->img,
			&env->screen_shot->bpp, &env->screen_shot->size_line,
			&env->screen_shot->endian);
	}
	while (y < UI_HEIGHT)
	{
		x = 1;
		while (x < WIDTH - MINI_M_SIZE)
		{
			my_mlx_pixel_put(env->screen_shot, x, y, get_screen_color(env->mlx, env->mlx_win, x, y));
			x++;
		}
		y++;
	}
}
