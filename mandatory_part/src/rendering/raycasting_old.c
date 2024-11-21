/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_old.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:54:02 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/21 15:54:06 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "raycasting_image_handler.c" */

// void	put_wall_slice(t_img *frame, int i, double *pos, double *wall_pos,
// 		t_env *env)
// {
// 	double	wall_height;

// 	put_bg(frame, i, env);
// 	if (env->data->frame_dist < 0)
// 		env->data->frame_dist *= -1;
// 	if (!(fabs(env->data->frame_dist) < 1e-6))
// 		wall_height = (HEIGHT / env->data->frame_dist) * (FOV_MOD
// 			/ ((double)Y_FOV * 2) * M_PI / 2.0);
// 	else
// 		wall_height = HEIGHT;
// 	if (is_whole_t(wall_pos[0], 1e-6) && wall_pos[0] >= pos[0])
// 		key_image_onto_walls(frame, env->west_wall, i, ceil(wall_pos[1])
// 			- wall_pos[1], wall_height);
// 	else if (is_whole_t(wall_pos[0], 1e-6) && wall_pos[0] <= pos[0])
// 		key_image_onto_walls(frame, env->east_wall, i, wall_pos[1],
// 			wall_height);
// 	else if (is_whole_t(wall_pos[1], 1e-6) && wall_pos[1] <= pos[2])
// 		key_image_onto_walls(frame, env->south_wall, i, ceil(wall_pos[0])
// 			- wall_pos[0], wall_height);
// 	else if (is_whole_t(wall_pos[1], 1e-6) && wall_pos[1] >= pos[2])
// 		key_image_onto_walls(frame, env->north_wall, i, wall_pos[0],
// 			wall_height);
// 	else
// 		printf("%lf, %lf\n", wall_pos[0], wall_pos[1]);
// }

// int	is_touching_wall(t_data *data, double *pos, double *new_pos)
// {
// 	if (new_pos[0] < 0.9 || new_pos[2] < 0.9 || new_pos[2] >= data->true_lines)
// 		return (0);
// 	if (is_whole_t(new_pos[0], 1e-6))
// 	{
// 		if (data->map_copy[(int)floor(new_pos[2])][(int)round(new_pos[0])
// 			- (pos[0] > new_pos[0])] == '1')
// 			return (1);
// 	}
// 	if (is_whole_t(new_pos[2], 1e-6))
// 	{
// 		if (data->map_copy[(int)round(new_pos[2])
// 			- (pos[2] > new_pos[2])][(int)floor(new_pos[0])] == '1')
// 			return (1);
// 	}
// 	return (0);
// }

// int	get_wall_dist(double *pos, double dirx, double *wall_pos, t_env *env)
// {
// 	double	new_pos[3] = {pos[0], pos[1], pos[2]};
// 	double	dir[2] = {dirx, 0.0};
// 	double	step;
// 	double	distance;
// 	step = 1e-6;
// 	distance = 0;
// 	while (1)
// 	{
// 		to_border(new_pos, dir, new_pos);
// 		if (is_touching_wall(env->data, pos, new_pos) != 0)
// 			break ;
// 		get_new_pos3(new_pos, dir, step, new_pos);
// 		distance = get_distance3(pos, new_pos);
// 		if (RENDER_DISTANCE - distance < 0)
// 			return (0);
// 	}
// 	if (is_whole_t(new_pos[0], 1e-6) && is_whole_t(new_pos[2], 1e-6))
// 		return (get_wall_dist(pos, dirx + 1e-6, wall_pos, env));
// 	distance = get_distance3(pos, new_pos);
// 	env->data->frame_dist = distance;
// 	wall_pos[0] = new_pos[0];
// 	wall_pos[1] = new_pos[2];
// 	return (1);
// }

// void	make_frame(t_img *frame, double *pos, double dir, t_env *env)
// {
// 	int		i;
// 	double	*wall_pos;
// 	double	dirx;

// 	i = 0;
// 	wall_pos = ft_malloc(2 * sizeof(double));
// 	dirx = dir - X_FOV / 2;
// 	while (i < WIDTH)
// 	{
// 		while (dirx < 0)
// 			dirx += 360;
// 		while (dirx >= 360)
// 			dirx -= 360;
// 		if (get_wall_dist(pos, dirx, wall_pos, env))
// 		{
// 			env->data->frame_dist *= cos(degrees_to_radians(dirx - dir));
// 			put_wall_slice(frame, WIDTH - i, pos, wall_pos, env);
// 			dirx = atan2(WIDTH / 2 - (i - 0.5), (int)((WIDTH / 2) / tan(M_PI
// 						/ 180 * (X_FOV / 2)))) * (180.0 / M_PI) + dir;
// 		}
// 		i++;
// 	}
// 	ft_free(wall_pos);
// }