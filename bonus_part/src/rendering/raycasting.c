/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 05:48:37 by tlaukat           #+#    #+#             */
/*   Updated: 2024/11/18 05:48:37 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	set_raycast(t_raycast *rc, double *pos)
{
	while (rc->dirx < 0)
		rc->dirx += 360;
	while (rc->dirx > 360)
		rc->dirx -= 360;
	rc->dir[0] = rc->dirx;
	rc->dir[1] = 0.0;
	rc->pos[0] = pos[0];
	rc->pos[1] = pos[1];
	rc->pos[2] = pos[2];
	rc->new_pos[0] = pos[0];
	rc->new_pos[1] = pos[1];
	rc->new_pos[2] = pos[2];
}

void	put_wall_slice(t_img *frame, t_raycast *rc, t_env *env)
{
	if (env->data->pic_ceiling && env->data->pic_floor)
		put_bg_slice(frame, WIDTH - rc->i, env);
	else
		put_bg(frame, WIDTH - rc->i, env);
	if (rc->frame_dist < 0)
		rc->frame_dist *= -1;
	if (!(fabs(rc->frame_dist) < 1e-6))
		rc->wall_height = (HEIGHT / rc->frame_dist) * (FOV_MOD / ((double)Y_FOV
				* 2) * M_PI / 2.0);
	else
		rc->wall_height = HEIGHT;
	if (is_whole_t(rc->wall_pos[0], 1e-6) && rc->wall_pos[0] >= rc->pos[0])
		img_to_wall(frame, env->west_wall, rc, ceil(rc->wall_pos[1])
			- rc->wall_pos[1]);
	else if (is_whole_t(rc->wall_pos[0], 1e-6) && rc->wall_pos[0] <= rc->pos[0])
		img_to_wall(frame, env->east_wall, rc, rc->wall_pos[1]);
	else if (is_whole_t(rc->wall_pos[1], 1e-6) && rc->wall_pos[1] <= rc->pos[2])
		img_to_wall(frame, env->south_wall, rc, ceil(rc->wall_pos[0])
			- rc->wall_pos[0]);
	else if (is_whole_t(rc->wall_pos[1], 1e-6) && rc->wall_pos[1] >= rc->pos[2])
		img_to_wall(frame, env->north_wall, rc, rc->wall_pos[0]);
	else
		printf("Error at: %lf, %lf\n", rc->wall_pos[0], rc->wall_pos[1]);
}

int	is_touching_wall(t_data *data, double *pos, double *new_pos)
{
	if (new_pos[0] < 0.9 || new_pos[2] < 0.9 || new_pos[2] >= data->true_lines)
		return (0);
	if (is_whole_t(new_pos[0], 1e-6))
	{
		if (data->map_copy[(int)floor(new_pos[2])][(int)round(new_pos[0])
			- (pos[0] > new_pos[0])] == '1')
			return (1);
	}
	if (is_whole_t(new_pos[2], 1e-6))
	{
		if (data->map_copy[(int)round(new_pos[2])
			- (pos[2] > new_pos[2])][(int)floor(new_pos[0])] == '1')
			return (1);
	}
	return (0);
}

int	get_wall_dist(t_raycast *rc, t_env *env)
{
	double	step;
	double	distance;

	set_raycast(rc, rc->pos);
	step = 1e-6;
	distance = 0;
	while (1)
	{
		to_border(rc->new_pos, rc->dir, rc->new_pos);
		if (is_touching_wall(env->data, rc->pos, rc->new_pos) != 0)
			break ;
		get_new_pos3(rc->new_pos, rc->dir, step, rc->new_pos);
		distance = get_distance3(rc->pos, rc->new_pos);
		if (RENDER_DISTANCE - distance < 0)
			return (0);
	}
	if (is_whole_t(rc->new_pos[0], 1e-6) && is_whole_t(rc->new_pos[2], 1e-6))
		return (rc->dirx += 0.1, get_wall_dist(rc, env));
	distance = get_distance3(rc->pos, rc->new_pos);
	rc->frame_dist = distance;
	rc->wall_pos[0] = rc->new_pos[0];
	rc->wall_pos[1] = rc->new_pos[2];
	return (1);
}

void	make_frame(t_img *frame, double *pos, double dir, t_env *env)
{
	t_raycast *rc;

	rc = ft_malloc(sizeof(t_raycast));
	rc->dirx = dir - X_FOV / 2;
	rc->wall_pos[0] = 0;
	rc->wall_pos[1] = 0;
	rc->wall_pos[2] = 0;
	rc->i = 0;
	while (rc->i < WIDTH)
	{
		set_raycast(rc, pos);
		if (get_wall_dist(rc, env))
		{
			rc->frame_dist *= cos(degrees_to_radians(rc->dirx - dir));
			put_wall_slice(frame, rc, env);
			rc->dirx = atan2(WIDTH / 2 - (rc->i - 0.5), (int)((WIDTH / 2)
					/ tan(M_PI / 180 * (X_FOV / 2)))) * (180.0 / M_PI) + dir;
		}
		rc->i++;
	}
	ft_free(rc);
}