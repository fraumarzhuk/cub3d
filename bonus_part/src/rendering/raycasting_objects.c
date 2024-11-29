#include "../../inc/cub.h"
#define Object_Width = 0.2
#define Object_Min_dist = 0.4

void	find_intersection(t_raycast *rc, double *obj, double *intersect)
{
	float	V1_x;
	float	V1_y;
	float	V2_x;
	float	V2_y;

	V1_x = cos(degrees_to_radians(θ1));
	V1_y = sin(degrees_to_radians(θ1));
	V2_x = cos(degrees_to_radians(θ1 + 90));
	V2_y = sin(degrees_to_radians(θ1 + 90));
	intersect[0] = (rc->new_pos[0] * V2_y - rc->new_pos[2] * V2_x + obj[0]
		* V1_y - obj[1] * V1_x) / (V1_x * V2_y - V1_y * V2_x);
	intersect[1] = (rc->new_pos[2] * V2_x - rc->new_pos[0] * V2_y + obj[1]
		* V1_x - obj[0] * V1_y) / (V1_x * V2_y - V1_y * V2_x);
}

void	check_objects(t_raycast *rc)
{
	double	obj[2];
	double	intersect[2];

    //intersect[2] = 0.5;
	if (is_whole_t(rc->new_pos[0], 1e-6))
	{
		obj[1] = floor(rc->new_pos[2]) + 0.5;
		obj[0] = round(new_pos[0]) + 0.5 - (rc->pos[0] > rc->new_pos[0]);
	}
	if (is_whole_t(rc->new_pos[2], 1e-6))
	{
		obj[0] = floor(rc->new_pos[0]) + 0.5;
		obj[1] = round(new_pos[2]) + 0.5 - (rc->pos[2] > rc->new_pos[2]);
	}
	find_intersection(rc, obj, intersect);
    if(get_distance2(obj, intersect) <= Object_Width)
    {
        
    }

}
