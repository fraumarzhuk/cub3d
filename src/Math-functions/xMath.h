/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xMath.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:17:23 by tlaukat           #+#    #+#             */
/*   Updated: 2024/10/28 16:31:20 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XMATH_H
# define XMATH_H
# include <math.h>
# ifndef M_PI
#  define M_PI 3.1415926
# endif

/*3D. Calculates the distance between two points*/
double	get_distance3(double *pos1, double *pos2);

/*2D. Calculates the distance between two points*/
double	get_distance2(double *pos1, double *pos2);

/*3D. calculates the new position for a specific distance and direction*/
void	get_new_pos3(double *pos, double dir[2], double dist, double *new_pos);

/*2D. calculates the new position for a specific distance and direction*/
void	get_new_pos2(double *x, double *y, double dir, double dist);

/*3D. Calculates the distance to the next wall.
A wall is a plane where either x, y or z is a whole number*/
double	distance_to_border(double *pos, double dir[2]);

/*3D. Calculates the next pos touching a wall.
A wall is a plane where either x, y or z is a whole number*/
void	to_border(double *pos, double dir[2], double *new_pos);

/*Converts a degree value into a radian*/
double	degrees_to_radians(double degrees);
#endif
