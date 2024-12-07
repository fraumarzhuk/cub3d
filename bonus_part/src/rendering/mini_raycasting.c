/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:10:01 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/07 15:17:55 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

bool	touch(double px, double py, t_env *env)
{
	int	x;
	int	y;

	x = px / BLOCKW;
	y = py / BLOCKH;
	if (env->data->map_copy[y][x] && is_wall_mm(env->data->map_copy[y][x]))
		return (true);
	return (false);
}

void	cast_mini_ray(t_player *player, t_env *env)
{
	float		angle;
	double		i;

	angle = player->angle;
	i = 0;
	draw_line(player->x, player->y, angle, env);
	while (i < 30)
	{
		draw_line(player->x, player->y, angle - i, env);
		draw_line(player->x, player->y, angle + i, env);
		i += 1;
	}
}

void	draw_line(double px, double py, float angle, t_env *env)
{
	double	mm_ray_x;
	double	mm_ray_y;

	mm_ray_x = MINI_M_SIZE / 2;
	mm_ray_y = MINI_M_SIZE / 2;
	while (!touch(px, py, env))
	{
		mm_ray_x += cos(degrees_to_radians(angle));
		mm_ray_y += sin(degrees_to_radians(angle));
		px += cos(degrees_to_radians(angle));
		py += sin(degrees_to_radians(angle));
		mm_pixel_put(mm_ray_x, mm_ray_y, RAYCOLOR, env);
	}
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
// 		mm_pixel_put((int)mm_ray_x, (int)mm_ray_y, RAYCOLOR, env);
// 	}
// }