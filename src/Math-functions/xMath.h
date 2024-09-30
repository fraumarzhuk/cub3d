/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xMath.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:17:23 by tlaukat           #+#    #+#             */
/*   Updated: 2024/09/28 03:17:23 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XMATH_H
# define XMATH_H
# include <math.h>
# ifndef M_PI
#  define M_PI 3.1415926
# endif

/*3D. Calculates the distance between two points*/
float	get_distance3(float *pos1, float *pos2);

/*2D. Calculates the distance between two points*/
float	get_distance2(float *pos1, float *pos2);

/*3D. calculates the new position for a specific distance and direction*/
void	get_new_pos3(float *pos, float dir[2], float dist, float *new_pos);

/*2D. calculates the new position for a specific distance and direction*/
void	get_new_pos2(float *pos, float dir[2], float dist, float *new_pos);

/*3D. Calculates the distance to the next wall.
A wall is a plane where either x, y or z is a whole number*/
float	distance_to_wall(float *pos, float dir[2]);

/*3D. Calculates the next pos touching a wall.
A wall is a plane where either x, y or z is a whole number*/
void	to_wall(float *pos, float dir[2], float *new_pos);

/*Converts a degree value into a radian*/
float	degrees_to_radians(float degrees);
#endif
