/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:00:25 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/01 15:01:05 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

bool	touch(double px, double py, t_env *env)
{
	int	x;
	int	y;

	x = px / BLOCKW;
	y = py / BLOCKH;
	if (env->data->map_copy[y][x] && env->data->map_copy[y][x] == '1')
		return (true);
	return (false);
}

void	cast_mini_ray(t_player *player, t_env *env)
{
	double	mm_ray_x;
	double	mm_ray_y;

	mm_ray_x = MINI_M_SIZE / 2;
	mm_ray_y = MINI_M_SIZE / 2;
	player->dir_x = player->x;
	player->dir_y = player->y;
	while (!touch(player->dir_x, player->dir_y, env))
	{
		mm_ray_x += cos(degrees_to_radians(player->angle)) * SPEED;
		mm_ray_y += sin(degrees_to_radians(player->angle) * SPEED);
		player->dir_x += cos(degrees_to_radians(player->angle)) * SPEED;
		player->dir_y += sin(degrees_to_radians(player->angle)) * SPEED;
		my_pixel_put(mm_ray_x, mm_ray_y, RAYCOLOR, env);
	}
}
