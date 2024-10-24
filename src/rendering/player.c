/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:05:47 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/24 15:54:36 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void move_player(t_player *player)
{
	int	speed;

	speed = 1;
	if (player->key_up)
		player->y -=speed;
	if (player->key_down)
		player->y += speed;
	if (player->key_left)
		player->x -= speed;
	if (player->key_right)
		player->x += speed;
}

int draw_loop(t_env *env)
{
	t_player *player = env->player;
	move_player(player);
	draw_square(player->x, player->y, 1, 0x00FF00, env);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img->img, 0, 0);
	return (1);
}