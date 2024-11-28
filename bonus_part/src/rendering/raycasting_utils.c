#include "../../inc/cub.h"

int	is_wall(char c, t_raycast *rc)
{
	rc->wall_char = c;
	if (c == '1' || c == 'B' || c == 'M' || c == 'A')
		return (1);
	return (0);
}

t_img	*get_wall_img(t_env *env, t_raycast *rc)
{
	if (rc->wall_char == '1')
		return (rc->wall_char = rc->facing, get_wall_img(env, rc));
	if (rc->wall_char == 'N')
		return (env->north_wall);
	if (rc->wall_char == 'S')
		return (env->south_wall);
	if (rc->wall_char == 'E')
		return (env->east_wall);
	if (rc->wall_char == 'W')
		return (env->west_wall);
	if (rc->wall_char == 'B')
		return (env->beer_shop);
	if (rc->wall_char == 'M')
		return (env->brezel_shop);
	if (rc->wall_char == 'A')
		return (env->pfandautomat);
	return (NULL);
}

char	get_facing(t_raycast *rc)
{
	if (is_whole_t(rc->wall_pos[0], 1e-6) && rc->wall_pos[0] >= rc->pos[0])
		return (rc->f_w_pos = ceil(rc->wall_pos[1]) - rc->wall_pos[1], 'W');
	else if (is_whole_t(rc->wall_pos[0], 1e-6) && rc->wall_pos[0] <= rc->pos[0])
		return (rc->f_w_pos = rc->wall_pos[1], 'E');
	else if (is_whole_t(rc->wall_pos[1], 1e-6) && rc->wall_pos[1] <= rc->pos[2])
		return (rc->f_w_pos = ceil(rc->wall_pos[0]) - rc->wall_pos[0], 'S');
	else if (is_whole_t(rc->wall_pos[1], 1e-6) && rc->wall_pos[1] >= rc->pos[2])
		return (rc->f_w_pos = rc->wall_pos[0], 'N');
	else
		printf("g_f: Error at: %lf, %lf\n", rc->wall_pos[0], rc->wall_pos[1]);
	rc->f_w_pos = 0.0;
	rc->facing = 'N';
	return (rc->facing);
}
