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

#include "../../inc/cub_bonus.h"

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
	rc->facing = 0;
	rc->wall_char = 0;
	rc->wall_image = NULL;
	rc->pfand = NULL;
}

void	put_wall_slice(t_img *frame, t_raycast *rc, t_env *env)
{
	t_img	*image;

	if (rc->i == (int)(WIDTH / 2) && rc->frame_dist <= REACH_DISTANCE)
		env->data->looking_at = rc->wall_char;
	if (env->data->pic_ceiling || env->data->pic_floor)
		put_bg_slice(frame, WIDTH - rc->i, *rc->dir, env);
	else
		put_bg(frame, WIDTH - rc->i, env);
	if (rc->frame_dist < 0)
		rc->frame_dist *= -1;
	if (!(fabs(rc->frame_dist) < 1e-6))
		rc->wall_height = (HEIGHT / rc->frame_dist) * (FOV_MOD / ((double)Y_FOV
					* 2) * M_PI / 2.0);
	else
		rc->wall_height = HEIGHT;
	rc->facing = get_facing(rc);
	image = get_wall_img(env, rc);
	img_to_wall(frame, image, rc);
	print_object_slice(frame, rc, env);
}

int	is_touching_wall(t_raycast *rc, t_data *data, double *pos, double *np)
{
	char	map_char;

	if (np[0] < 0.9 || np[2] < 0.9 || np[2] >= data->true_lines)
		return (0);
	if (is_whole_t(np[0], 1e-6))
		map_char = data->map_copy[(int)floor(np[2])][(int)round(np[0])
			- (pos[0] > np[0])];
	if (is_whole_t(np[2], 1e-6))
		map_char = data->map_copy[(int)round(np[2])
			- (pos[2] > np[2])][(int)floor(np[0])];
	if (map_char == 'P')
		check_objects(rc);
	if (is_wall(map_char, rc))
		return (1);
	return (0);
}

int	get_wall_dist(t_raycast *rc, t_env *env)
{
	double	step;

	set_raycast(rc, rc->pos);
	step = 1e-6;
	rc->frame_dist = 0;
	while (1)
	{
		to_border(rc->new_pos, rc->dir, rc->new_pos);
		if (is_touching_wall(rc, env->data, rc->pos, rc->new_pos) != 0)
			break ;
		get_new_pos3(rc->new_pos, rc->dir, step, rc->new_pos);
		rc->frame_dist = get_distance3(rc->pos, rc->new_pos);
		if (RENDER_DISTANCE - rc->frame_dist < 0)
			return (0);
	}
	if (is_whole_t(rc->new_pos[0], 1e-6) && is_whole_t(rc->new_pos[2], 1e-6))
		return (rc->dirx += 0.1, get_wall_dist(rc, env));
	rc->frame_dist = get_distance3(rc->pos, rc->new_pos);
	rc->wall_pos[0] = rc->new_pos[0];
	rc->wall_pos[1] = rc->new_pos[2];
	return (1);
}

void	make_frame(t_img *frame, double *pos, double dir, t_env *env)
{
	t_raycast	*rc;

	rc = ft_malloc(sizeof(t_raycast));
	rc->dirx = dir - X_FOV / 2;
	rc->wall_pos[0] = 0;
	rc->wall_pos[1] = 0;
	rc->wall_pos[2] = 0;
	rc->i = 0;
	env->data->looking_at = '1';
	while (rc->i < WIDTH)
	{
		set_raycast(rc, pos);
		if (get_wall_dist(rc, env))
		{
			rc->frame_dist *= cos(degrees_to_radians(rc->dirx - dir));
			put_wall_slice(frame, rc, env);
			rc->dirx = atan2(WIDTH / 2 - (rc->i - 0.5), (int)((WIDTH / 2)
						/ tan(M_PI / 180 * (X_FOV / 2))))
				* (180.0 / M_PI) + dir;
		}
		rc->i++;
	}
	ft_free(rc);
}
