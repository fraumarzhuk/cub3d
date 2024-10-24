/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:05:47 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/24 16:29:23 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void move_player(t_player *player)
{
	int	speed;

	speed = 5;
	if (player->key_up)
		player->y -= speed;
	if (player->key_down)
		player->y += speed;
	if (player->key_left)
		player->x -= speed;
	if (player->key_right)
		player->x += speed;
}

void clear_image(t_env *env)
{
    for(int y = 0; y < HEIGHT; y++)
        for(int x = 0; x < WIDTH; x++)
            my_pixel_put(x, y, 0, env);
}

int draw_loop(t_env *env)
{
	t_player *player = env->player;
	move_player(player);
	clear_image(env);
	draw_square(player->x, player->y, 5, 0x00FF00, env);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img->img, 0, 0);
	return (1);
}