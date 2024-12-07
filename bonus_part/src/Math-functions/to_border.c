/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_border.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:17:29 by tlaukat           #+#    #+#             */
/*   Updated: 2024/12/07 15:52:12 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xMath.h"

void	set_d(double hor_rad, double ver_rad, double d[3])
{
	d[0] = cos(ver_rad) * cos(hor_rad);
	d[1] = sin(ver_rad);
	d[2] = cos(ver_rad) * sin(hor_rad);
}

void	set_dist(double pos, double d, double *dist)
{
	if (d > 0)
		*dist = ceil(pos) - pos;
	else if (d < 0)
		*dist = pos - floor(pos);
	else
		*dist = INFINITY;
}

double	distance_to_border(double *pos, double dir[2])
{
	double	hor_rad;
	double	ver_rad;
	double	d[3];
	double	dist[3];
	double	dist_to_border;

	hor_rad = degrees_to_radians(dir[0]);
	ver_rad = degrees_to_radians(dir[1]);
	set_d(hor_rad, ver_rad, d);
	set_dist(pos[0], d[0], &(dist[0]));
	set_dist(pos[1], d[1], &(dist[1]));
	set_dist(pos[2], d[2], &(dist[2]));
	dist_to_border = fmin(dist[0] / fabs(d[0]), fmin(dist[1] / fabs(d[1]),
				dist[2] / fabs(d[2])));
	return (dist_to_border);
}

void	to_border(double *pos, double dir[2], double *new_pos)
{
	double	dist;

	dist = distance_to_border(pos, dir);
	get_new_pos3(pos, dir, dist, new_pos);
}
