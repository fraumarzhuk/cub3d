/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:17:34 by tlaukat           #+#    #+#             */
/*   Updated: 2024/10/28 16:31:09 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xMath.h"

// calculates the new position for a
// specific distance and direction for 2D and 3D

// double * = [double x (L R), double y (height), double z (U D)]
void	get_new_pos3(double *pos, double dir[2], double dist, double *new_pos)
{
	double	hor_rad;
	double	ver_rad;
	double	dx;
	double	dy;
	double	dz;

	hor_rad = degrees_to_radians(dir[0]);
	ver_rad = degrees_to_radians(dir[1]);
	dx = dist * cos(ver_rad) * cos(hor_rad);
	dy = dist * sin(ver_rad);
	dz = dist * cos(ver_rad) * sin(hor_rad);
	new_pos[0] = pos[0] + dx;
	new_pos[1] = pos[1] + dy;
	new_pos[2] = pos[2] + dz;
}

// double * = [double x (L R), double y (U D)]
void	get_new_pos2(double *x, double *y, double dir, double dist)
{
	double	hor_rad;
	double	dx;
	double	dy;

	hor_rad = degrees_to_radians(dir);
	dx = dist * cos(hor_rad);
	dy = dist * sin(hor_rad);
	*x = *x + dx;
	*y = *y + dy;
}
