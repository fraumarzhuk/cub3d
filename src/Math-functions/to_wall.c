/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:17:29 by tlaukat           #+#    #+#             */
/*   Updated: 2024/09/28 03:17:29 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

void	set_d(float hor_rad, float ver_rad, float *d[3])
{
	*d[0] = cos(ver_rad) * cos(hor_rad);
	*d[1] = sin(ver_rad);
	*d[2] = cos(ver_rad) * sin(hor_rad);
}

void	set_dist(float pos, float d, float *dist)
{
	if (d > 0)
		*dist = ceil(pos) - pos;
	else if (d < 0)
		*dist = pos - floor(pos);
	else
		*dist = INFINITY;
}

float	distance_to_wall(float *pos, float dir[2])
{
	float	hor_rad;
	float	ver_rad;
	float	d[3];
	float	dist[3];
	float	dist_to_wall;

	hor_rad = degrees_to_radians(dir[0]);
	ver_rad = degrees_to_radians(dir[1]);
	set_d(hor_rad, ver_rad, &d);
	setdist(pos[0], d[0], &(dist[0]));
	setdist(pos[1], d[1], &(dist[1]));
	setdist(pos[2], d[2], &(dist[2]));
	dist_to_wall = fmin(dist[0] / fabs(d[0]), fmin(dist[1] / fabs(d[1]), dist[2]
			/ fabs(d[2])));
	return (dist_to_wall);
}

void	to_wall(float *pos, float dir[2], float *new_pos)
{
	float	dist;

	dist = distance_to_wall(pos, dir);
	get_new_pos3(pos, dir, dist, new_pos);
}
