/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:41:53 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/12 18:00:50 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int	mini_draw_loop(t_env *env)
{
	double	pos[3];

	move_player(env->player, env);
	draw_mini_map(env);
	pos[0] = env->player->x / BLOCKW;
	pos[1] = 0.5;
	pos[2] = env->player->y / BLOCKH;
	make_frame(env->scene_canvas, pos, env->player->angle, env);
	draw_ui(env, env->scene_canvas, 1);
	if (env->player->render_move)
		render_images_on_canvas(env);
	return (1);
}

void	draw_mini_map(t_env *env)
{
	double	px_offset;
	double	py_offset;
	int		y;

	if (!env->player->render_move)
		return ;
	clear_image(env->mini_map, MINI_M_SIZE, MINI_M_SIZE);
	env->draw_x = (MINI_M_SIZE - MINI_P) / 2;
	env->draw_y = (MINI_M_SIZE - MINI_P) / 2;
	px_offset = env->player->x - (env->player->xc * BLOCKW);
	py_offset = env->player->y - (env->player->yc * BLOCKH);
	draw_square(MINI_P, 0x00FF00, env);
	cast_mini_ray(env->player, env);
	y = 0;
	while (env->data->map_copy[y])
	{
		calculate_draw_xy(env, y, px_offset, py_offset);
		y++;
	}
	draw_mini_border(env);
	env->player->counter++;
}

void	calculate_draw_xy(t_env *env, int y, double px_offset, double py_offset)
{
	int	x;

	x = 0;
	while (env->data->map_copy[y][x])
	{
		if (is_wall_mm(env->data->map_copy[y][x]))
		{
			env->draw_x = x * BLOCKW -(env->player->xc * BLOCKW + px_offset)
				+ MINI_M_SIZE / 2;
			env->draw_y = y * BLOCKH - (env->player->yc * BLOCKH + py_offset)
				+ MINI_M_SIZE / 2;
			if (env->draw_x >= -BLOCKW && env->draw_x
				< MINI_M_SIZE && env->draw_y
				>= -BLOCKH && env->draw_y < MINI_M_SIZE)
			{
				if (is_wall_mm(env->data->map_copy[y][x]))
					draw_mini_map_walls(env, env->data->map_copy[y][x]);
			}
		}
		x++;
	}
}

void	draw_mini_border(t_env *env)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x++ < MINI_M_SIZE)
		mm_pixel_put(x, y, MINI_BORDER_C, env);
	x = 0;
	while (y++ < MINI_M_SIZE)
		mm_pixel_put(x, y, MINI_BORDER_C, env);
	y = MINI_M_SIZE - 1;
	while (x++ < MINI_M_SIZE - 1)
		mm_pixel_put(x, y, MINI_BORDER_C, env);
	x = MINI_M_SIZE - 1;
	y = 0;
	while (y++ < (MINI_M_SIZE - 1))
		mm_pixel_put(x, y, MINI_BORDER_C, env);
}

void draw_mini_map_walls(t_env *env, char position)
{
	int	color;

	if (position == 'A')
		color = A_BLOCK_COL;
	else if (position == 'B')
		color = BS_BLOCK_COL;
	else if (position == 'M')
		color = MS_BLOCK_COL;
	else
		color = BLOCK_COL;
	draw_filled_square(BLOCKH, color, env);
	draw_square(BLOCKH, 0x000000, env);
}
