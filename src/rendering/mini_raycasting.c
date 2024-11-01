/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:10:01 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/01 16:39:29 by mzhukova         ###   ########.fr       */
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

// void	cast_ray(t_player *player, t_env *env)
// {
// 	double	ray_pos[2];
// 	double	ray_dir[2]; //pos touching a wall?
// 	double	new_pos[2];
// 	double	distance;
// 	double	mm_ray_x;
// 	double	mm_ray_y;

// 	mm_ray_x = MINI_M_SIZE / 2;
// 	mm_ray_y = MINI_M_SIZE / 2;
// 	ray_pos[0] = player->x;
// 	ray_pos[1] = player->y;
// 	ray_dir[0] = cos(degrees_to_radians(player->angle)) * SPEED;
// 	ray_dir[1] = sin(degrees_to_radians(player->angle)) * SPEED;

// 	while (!touch(ray_pos[0], ray_pos[1], env))
// 	{
// 		distance = distance_to_border(ray_pos, ray_dir);
// 		get_new_pos2(&ray_pos[0], &ray_pos[1], player->angle, distance);
// 		ray_pos[0] = new_pos[0];
// 		ray_pos[1] = new_pos[1];
// 		mm_ray_x += new_pos[0];
// 		mm_ray_y += new_pos[1];
// 		my_pixel_put((int)mm_ray_x, (int)mm_ray_y, RAYCOLOR, env);
// 	}
// }

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
