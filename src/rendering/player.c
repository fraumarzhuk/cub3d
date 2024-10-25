/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:05:47 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/25 15:38:43 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void move_player(t_player *player, t_env *env)
{
	int	speed;
	(void)env;
	speed = 3;
	if (player->key_up && player->y - speed >= 0)
		player->y -= speed;
	if (player->key_down && player->y + speed < HEIGHT)
		player->y += speed;
	if (player->key_left && player->x - speed >= 0)
		player->x -= speed;
	if (player->key_right && player->x + speed < WIDTH)
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
	move_player(player, env);
	clear_image(env);
	draw_square(mini_m_w/2, mini_m_h/2, 5, 0x00FF00, env);
	draw_map(env);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img->img, 0, 0);
	return (1);
}
