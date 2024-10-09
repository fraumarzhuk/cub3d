/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:17:37 by tlaukat           #+#    #+#             */
/*   Updated: 2024/10/07 02:24:46 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xMath.h"

// calculates the distance between two points in 3D or 2D

// double* = [double x (L R), double y (height), double z (U D)]
double	get_distance3(double *pos1, double *pos2)
{
	double	dx;
	double	dy;
	double	dz;
	double	distance;

	dx = pos2[0] - pos1[0];
	dy = pos2[1] - pos1[1];
	dz = pos2[2] - pos1[2];
	distance = sqrt(dx * dx + dy * dy + dz * dz);
	return (distance);
}

// double * = [double x (L R), double y (U D)]
double	get_distance2(double *pos1, double *pos2)
{
	double	dx;
	double	dy;
	double	distance;

	dx = pos1[0] - pos2[0];
	dy = pos1[1] - pos2[1];
	distance = sqrtf(dx * dx + dy * dy);
	return (distance);
}
