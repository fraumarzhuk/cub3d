/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:05:47 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/28 12:27:05 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void move_player(t_player *player, t_env *env)
{
	int speed = SPEED;
	double next_x = player->x;
	double next_y = player->y;

	if (player->key_up && player->y - speed >= 0)
		next_y -= speed;
	if (player->key_down && player->y + speed < HEIGHT)
		next_y += speed;
	if (player->key_left && player->x - speed >= 0)
		next_x -= speed;
	if (player->key_right && player->x + speed < WIDTH)
		next_x += speed;
	int next_matrix_x = next_x / BLOCKW;
	int next_matrix_y = next_y / BLOCKH;

	if (env->data->map_copy[next_matrix_y][next_matrix_x] != '1')
	{
		player->x = next_x;
		player->y = next_y;
		player->xc = next_matrix_x;
		player->yc = next_matrix_y;
	}
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
	draw_square(mini_m_w/2, mini_m_h/2, mini_p, 0x00FF00, env);
	draw_map(env);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img->img, 0, 0);
	return (1);
}
