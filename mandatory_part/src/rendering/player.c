/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:05:47 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/20 12:57:28 by mzhukova         ###   ########.fr       */
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
	if (player->key_up || player->key_down || player->key_left
		|| player->key_right || player->right_rotate || player->left_rotate)
	{
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
		if (env->data->map_copy[(int)next_y
				/ BLOCKH][(int)next_x / BLOCKW] != '1')
			set_new_coords(player, next_x, next_y);
	}
}

void	set_new_coords(t_player *player, double next_x, double next_y)
{
	player->x = next_x;
	player->y = next_y;
	player->xc = (int)next_x / BLOCKW;
	player->yc = (int)next_y / BLOCKH;
	player->render_move = true;
}
