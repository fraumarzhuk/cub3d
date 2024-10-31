/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:41:53 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/31 15:06:52 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void draw_map(t_env *env)
{
	double px_offset;
	double py_offset;
	int		x;
	int		y;
	px_offset = env->player->x - (env->player->xc * BLOCKW);
	py_offset = env->player->y - (env->player->yc * BLOCKH);
	y = 0;
	while(env->data->map_copy[y])
	{
		x = 0;
		while (env->data->map_copy[y][x])
		{
			if (env->data->map_copy[y][x] == '1')
			{
				double block_world_x = x * BLOCKW;
				double block_world_y = y * BLOCKH;
				int draw_x = block_world_x - (env->player->xc * BLOCKW + px_offset) + mini_m_w / 2;
				int draw_y = block_world_y - (env->player->yc * BLOCKH + py_offset) + mini_m_h / 2;
				if (draw_x >= -BLOCKW && draw_x < mini_m_w && draw_y >= -BLOCKH && draw_y < mini_m_h)
					draw_square(draw_x, draw_y, BLOCKH, BLOCK_COL, env);
			}
			x++;
		}
		y++;
	}
}

void draw_mini_border(t_env *env)
{
	int x;
	int	y;
	x = 0;
	y = 0;
	while (x++ < mini_m_w)
		my_pixel_put(x, y, MINI_BORDER_C, env);
	x = 0;
	while (y++ < mini_m_h)
		my_pixel_put(x, y, MINI_BORDER_C, env);
	y = mini_m_h - 1;
	while (x++ < mini_m_w - 1)
		my_pixel_put(x, y, MINI_BORDER_C, env);
	x = mini_m_w - 1;
	y = 0;
	while (y++ < (mini_m_h - 1))
		my_pixel_put(x, y, MINI_BORDER_C, env);
	
}