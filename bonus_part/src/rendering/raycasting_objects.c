/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:48:57 by tlaukat           #+#    #+#             */
/*   Updated: 2024/12/05 18:48:57 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	next_object(t_raycast *rc)
{
	t_object	*pfand;

	pfand = rc->pfand->next;
	ft_free(rc->pfand);
	rc->pfand = pfand;
}

void	print_object_slice(t_img *frame, t_raycast *rc, t_env *env)
{
	int	y;
	int	y_top;
	int	y_bottom;
	int	color;
	int	object_height;

	while (rc->pfand)
	{
		object_height = (int)(Object_Width * env->pfand->height
				/ env->pfand->width * HEIGHT / rc->pfand->dist);
		y_bottom = HEIGHT / 2 + ((HEIGHT / rc->pfand->dist) * (FOV_MOD
					/ ((double)Y_FOV * 2) * M_PI / 2.0)) / 2;
		y = (int)fmin(HEIGHT, y_bottom);
		y_top = y_bottom - object_height;
		while (y >= 0 && y >= y_top)
		{
			color = get_image_pixel(env->pfand, rc->pfand->pos / Object_Width
					+ 0.5, fmax(0, (y - y_top) / (double)(object_height)));
			if (color != (int)0xFF000000)
				my_mlx_pixel_put(frame, WIDTH - rc->i, y, color);
			y--;
		}
		next_object(rc);
	}
}

void	find_intersection(t_raycast *rc, double *obj, double *intersect)
{
	double	dx1;
	double	dy1;
	double	dx2;
	double	dy2;
	double	t;

	dx1 = cos(degrees_to_radians(rc->dirx));
	dy1 = sin(degrees_to_radians(rc->dirx));
	dx2 = cos(degrees_to_radians(rc->dirx + 90));
	dy2 = sin(degrees_to_radians(rc->dirx + 90));
	t = (obj[0] - rc->new_pos[0]) * dy2 - (obj[1] - rc->new_pos[2]) * dx2;
	t /= dx1 * dy2 - dx2 * dy1;
	intersect[0] = rc->new_pos[0] + t * dx1;
	intersect[1] = rc->new_pos[2] + t * dy1;
	intersect[2] = intersect[1];
}

void	check_objects(t_raycast *rc)
{
	double		obj[2];
	double		intersect[3];
	t_object	*pfand;

	if (is_whole_t(rc->new_pos[0], 1e-6))
	{
		obj[1] = floor(rc->new_pos[2]) + 0.5;
		obj[0] = round(rc->new_pos[0]) + 0.5 - (rc->pos[0] > rc->new_pos[0]);
	}
	if (is_whole_t(rc->new_pos[2], 1e-6))
	{
		obj[0] = floor(rc->new_pos[0]) + 0.5;
		obj[1] = round(rc->new_pos[2]) + 0.5 - (rc->pos[2] > rc->new_pos[2]);
	}
	find_intersection(rc, obj, intersect);
	if (get_distance2(obj, intersect) > Object_Width / 2)
		return ;
	pfand = ft_malloc(sizeof(t_object));
	pfand->pos = get_distance2(obj, intersect) * (1 + (-2
				* (((intersect[0] <= obj[0]) - (intersect[0] == obj[0])
						* (intersect[1] <= obj[1])) * (rc->dirx > 90))));
	intersect[1] = rc->pos[1];
	pfand->dist = get_distance3(rc->pos, intersect);
	pfand->next = rc->pfand;
	rc->pfand = pfand;
}
