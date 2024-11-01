/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:05:47 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/01 15:04:12 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

float	new_angle(float angle, float angle_speed, bool left, bool right)
{
	if (left)
		angle -= angle_speed;
	if (right)
		angle += angle_speed;
	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return (angle);
}

void	move_player(t_player *player, t_env *env)
{
	double	next_x;
	double	next_y;

	next_x = player->x;
	next_y = player->y;
	player->angle = new_angle(player->angle, ANGLE_SPEED,
			player->left_rotate, player->right_rotate);
	if (player->key_up && player->y - SPEED >= 0)
		get_new_pos2(&next_x, &next_y, player->angle, SPEED);
	if (player->key_down && player->y + SPEED < HEIGHT)
		get_new_pos2(&next_x, &next_y, player->angle + 180, SPEED);
	if (player->key_left && player->x - SPEED >= 0)
		get_new_pos2(&next_x, &next_y, player->angle - 90, SPEED);
	if (player->key_right && player->x + SPEED < WIDTH)
		get_new_pos2(&next_x, &next_y, player->angle + 90, SPEED);
	if (env->data->map_copy[(int)next_y / BLOCKH][(int)next_x / BLOCKW] != '1')
	{
		player->x = next_x;
		player->y = next_y;
		player->xc = (int)next_x / BLOCKW;
		player->yc = (int)next_y / BLOCKH;
	}
}

void	draw_triangle(int size, int x, int y, int color, t_env *env)
{
	int	i;
	int	start_x;
	int	end_x;
	int	height;
	int	j;

	i = 0;
	start_x = 0;
	end_x = 0;
	height = 0;
	j = 0;
	y = y - size / 2;
	height = (int)(size * sin((80) * PI / 180.0));
	while (i < height)
	{
		start_x = x - (i * size) / height / 2;
		end_x = x + (i * size) / height / 2;
		j = start_x;
		while (j <= end_x)
		{
			my_pixel_put(j, y + i, color, env);
			j++;
		}
		i++;
	}
}
