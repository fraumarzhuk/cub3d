/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:41:53 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/28 14:02:10 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

// void init_minimap(t_img *img, t_data *data, t_env *env)
// {
// 	draw_map(env);
// 	draw_square(WIDTH / 2, HEIGHT / 2, 15, 0x00ff00, env);
// }

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
