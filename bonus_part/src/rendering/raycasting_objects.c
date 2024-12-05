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
		y_bottom = ((HEIGHT / rc->pfand->dist) * (FOV_MOD / ((double)Y_FOV * 2)
				* M_PI / 2.0));
		y = (int)fmin(HEIGHT, y_bottom);
		y_top = y_bottom - object_height;
		printf("Printing pfand from %d to %d at %d with dist: %f\n", y_top,
			y_bottom, WIDTH - rc->i, rc->pfand->dist);
		while (y >= 0 && y >= y_top)
		{
			// double compact_position = rc->pfand->pos / Object_Width + 0.5;
			color = get_image_pixel(env->pfand, rc->pfand->pos / Object_Width
				+ 0.5, (y - y_top) / (double)(object_height));
			/*printf("Color calculation: rc->pfand->pos = %f, Object_Width = %f,
				y = %d, y_bottom = %d, y_top = %d Result: %f, %f \n",
				rc->pfand->pos, Object_Width, y, y_bottom, y_top,
				(rc->pfand->pos + Object_Width / 2) / Object_Width, (y - y_top)
				/ (double)(y_bottom - y_top));*/
			if (color != (int)0xFF000000)
				my_mlx_pixel_put(frame, WIDTH - rc->i, y, color);
			y--;
		}
		next_object(rc);
	}
}

void	find_pfandamountintersection(t_raycast *rc, double *obj, double *intersect)
{
	float	V1_x;
	float	V1_y;
	float	V2_x;
	float	V2_y;
	double	t;

	V1_x = cos(degrees_to_radians(rc->dirx));
	V1_y = sin(degrees_to_radians(rc->dirx));
	V2_x = cos(degrees_to_radians(rc->dirx + 90));
	V2_y = sin(degrees_to_radians(rc->dirx + 90));
	t = fabs((obj[0] - rc->new_pos[0] + 0.5) * V2_x + (obj[1] - rc->new_pos[2]
			+ 0.5) * V2_y);
	// t = (obj[0] - rc->new_pos[0]) * V2_x + (obj[1] - rc->new_pos[2]) * V2_y;
	intersect[0] = rc->new_pos[0] + V1_x * t;
	intersect[1] = rc->new_pos[2] + V1_y * t;
	intersect[2] = intersect[1];
	/* intersect[0] = (rc->new_pos[0] * V2_y - rc->new_pos[2] * V2_x + obj[0]
		* V1_y - obj[1] * V1_x) / (V1_x * V2_y - V1_y * V2_x);
	intersect[1] = (rc->new_pos[2] * V2_x - rc->new_pos[0] * V2_y + obj[1]
		* V1_x - obj[0] * V1_y) / (V1_x * V2_y - V1_y * V2_x);
	*/
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
	find_pfandamountintersection(rc, obj, intersect);
	if (get_distance2(obj, intersect) > Object_Width / 2)
		return ;
	pfand = ft_malloc(sizeof(t_object));
	pfand->pos = get_distance2(obj, intersect) * (-1
		* (((intersect[0] <= obj[0]) - (intersect[0] == obj[0])
				* (intersect[1] <= obj[1])) * (rc->dirx > 90)));
	intersect[1] = rc->pos[1];
	pfand->dist = get_distance3(rc->pos, intersect);
	pfand->next = rc->pfand;
	rc->pfand = pfand;
}
