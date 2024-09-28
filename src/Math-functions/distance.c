/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:17:37 by tlaukat           #+#    #+#             */
/*   Updated: 2024/09/28 03:17:37 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xMath.h"

// calculates the distance between two points in 3D or 2D

// float* = [float x (L R), float y (height), float z (U D)]
float	get_distance3(float *pos1, float *pos2)
{
	float	dx;
	float	dy;
	float	dz;
	float	distance;

	dx = pos2[0] - pos1[0];
	dy = pos2[1] - pos1[1];
	dz = pos2[2] - pos2[2];
	distance = sqrt(dx * dx + dy * dy + dz * dz);
	return (distance);
}

// float * = [float x (L R), float y (U D)]
float	get_distance2(float *pos1, float *pos2)
{
	float	dx;
	float	dy;
	float	distance;

	dx = pos1[0] - pos2[0];
	dy = pos1[1] - pos2[1];
	distance = sqrtf(dx * dx + dy * dy);
	return (distance);
}
