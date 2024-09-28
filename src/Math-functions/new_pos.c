/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:17:34 by tlaukat           #+#    #+#             */
/*   Updated: 2024/09/28 03:17:34 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xMath.h"

// calculates the new position for a
// specific distance and direction for 2D and 3D

// float * = [float x (L R), float y (height), float z (U D)]
void	get_new_pos3(float *pos, float dir[2], float dist, float *new_pos)
{
	float	hor_rad;
	float	ver_rad;
	float	dx;
	float	dy;
	float	dz;

	hor_rad = degrees_to_radians(dir[0]);
	ver_rad = degrees_to_radians(dir[1]);
	dx = dist * cos(ver_rad) * cos(hor_rad);
	dy = dist * sin(ver_rad);
	dz = dist * cos(ver_rad) * sin(hor_rad);
	new_pos[0] = pos[0] + dx;
	new_pos[1] = pos[1] + dy;
	new_pos[2] = pos[2] + dz;
}

// float * = [float x (L R), float y (U D)]
void	get_new_pos2(float *pos, float dir[2], float dist, float *new_pos)
{
	float	hor_rad;
	float	dx;
	float	dy;

	hor_rad = degrees_to_radians(dir[0]);
	dx = dist * cos(hor_rad);
	dy = dist * sin(hor_rad);
	new_pos[0] = pos[0] + dx;
	new_pos[1] = pos[1] + dy;
}
