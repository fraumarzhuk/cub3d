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
	move_player(env->player, env);
	draw_mini_map(env);
	double pos[3] = {env->player->x / BLOCKW, 0.5, env->player->y / BLOCKH};
	make_frame(env->scene_canvas, pos, env->player->angle, env);
	render_images_on_canvas(env);
	//mlx_put_image_to_window(env->mlx, env->mlx_win, env->canvas->img, 0, 0);
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
	//draw_triangle(MINI_P, MINI_M_SIZE / 2, MINI_M_SIZE / 2, 0x00FF00, env);
	// draw_square(MINI_M_SIZE / 2 - (MINI_P / 4), MINI_M_SIZE / 2 - (MINI_P / 4), MINI_P/2, 0x00FF00, env);
	draw_square(MINI_M_SIZE / 2, MINI_M_SIZE / 2, MINI_P, 0x00FF00, env);
	px_offset = env->player->x - (env->player->xc * BLOCKW);
	py_offset = env->player->y - (env->player->yc * BLOCKH);
	y = 0;
	while (env->data->map_copy[y])
	{
		calculate_draw_xy(env, y, px_offset, py_offset);
		y++;
	}
	draw_mini_border(env);
	cast_mini_ray(env->player, env);
	env->player->counter++;
}

void	calculate_draw_xy(t_env *env, int y, double px_offset, double py_offset)
{
	int	draw_x;
	int	draw_y;
	int	x;

	x = 0;
	while (env->data->map_copy[y][x])
	{
		if (is_wall_mm(env->data->map_copy[y][x]))
		{
			draw_x = x * BLOCKW -(env->player->xc * BLOCKW + px_offset)
				+ MINI_M_SIZE / 2;
			draw_y = y * BLOCKH - (env->player->yc * BLOCKH + py_offset)
				+ MINI_M_SIZE / 2;
			if (draw_x >= -BLOCKW && draw_x < MINI_M_SIZE && draw_y
				>= -BLOCKH && draw_y < MINI_M_SIZE)
				{
					if (env->data->map_copy[y][x] == 'A')
						draw_square(draw_x, draw_y, BLOCKH, A_BLOCK_COL, env);
					else
						draw_square(draw_x, draw_y, BLOCKH, BLOCK_COL, env);
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
