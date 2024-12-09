/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:05:47 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/09 01:43:06 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

float	new_angle(float angle, float angle_speed, bool left, bool right)
{
	if (left)
		angle -= angle_speed;
	if (right)
		angle += angle_speed;
	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return (angle);
}

void	move_player(t_player *player, t_env *env)
{
	double	next_x;
	double	next_y;
	double	speed;

	next_x = player->x;
	next_y = player->y;
	speed = SPEED + (SPEED * (player->player_pos == BEER && BEER_SPRINT == 1));
	if ((player->key_up || player->key_down || player->key_left
			|| player->key_right || player->right_rotate || player->left_rotate
			|| player->mouse_on) && !player->display_bon)
	{
		if ((player->right_rotate || player->left_rotate) && !player->no_rotate)
			player->angle = new_angle(player->angle, ANGLE_SPEED,
					player->left_rotate, player->right_rotate);
		if (player->key_up && player->y - speed >= 0)
			get_new_pos2(&next_x, &next_y, player->angle, speed);
		if (player->key_down && player->y + speed < HEIGHT)
			get_new_pos2(&next_x, &next_y, player->angle + 180, speed);
		if (player->key_left && player->x - speed >= 0)
			get_new_pos2(&next_x, &next_y, player->angle - 90, speed);
		if (player->key_right && player->x + speed < WIDTH)
			get_new_pos2(&next_x, &next_y, player->angle + 90, speed);
		env->player->no_rotate = false;
		wall_slide(player, env, next_x, next_y);
	}
}

void	set_new_coords(t_env *env, double next_x, double next_y)
{
	if ((!is_wall_or_space(env->data->map_copy[(int)((next_y + MINI_P / 2.0)
					/ (double)BLOCKH)][(int)(next_x / (double)BLOCKW)])) &&
		(!is_wall_or_space(env->data->map_copy[(int)((next_y - MINI_P / 2)
					/ (double)BLOCKH)][(int)(next_x / (double)BLOCKW)])) &&
		(!is_wall_or_space(env->data->map_copy[(int)(floor(next_y
					/ (double)BLOCKH))][(int)floor((next_x + MINI_P / 2)
					/ (double)BLOCKW)])) &&
		(!is_wall_or_space(env->data->map_copy[(int)(floor(next_y
					/ (double)BLOCKH))][(int)floor((next_x - MINI_P
					/ 2) / (double)BLOCKW)])))
	{
		env->player->x = next_x;
		env->player->y = next_y;
		env->player->xc = (int)next_x / BLOCKW;
		env->player->yc = (int)next_y / BLOCKH;
		env->player->render_move = true;
	}
}

void	wall_slide(t_player *player, t_env *env, double next_x, double next_y)
{
	env->player->touches_h_wall = 0;
	env->player->touches_v_wall = 0;
	if (is_wall_or_space(env->data->map_copy[(int)(next_y
				/ (int)BLOCKH)][(int)((next_x + MINI_P / 2.0) / (int)BLOCKW)]))
		env->player->touches_h_wall = 1;
	if (is_wall_or_space(env->data->map_copy[(int)(next_y
				/ (int)BLOCKH)][(int)((next_x - MINI_P / 2.0) / (int)BLOCKW)]))
		env->player->touches_h_wall = -1;
	if (is_wall_or_space(env->data->map_copy[(int)((next_y + MINI_P / 2.0)
				/ (int)BLOCKH)][(int)(next_x / (int)BLOCKW)]))
		env->player->touches_v_wall = 1;
	if (is_wall_or_space(env->data->map_copy[(int)((next_y - MINI_P / 2.0)
				/ (int)BLOCKH)][(int)(next_x / (int)BLOCKW)]))
		env->player->touches_v_wall = -1;
	set_new_coords(env, next_x, next_y);
	if (env->player->touches_h_wall == 0 && env->player->touches_v_wall == 0)
		return ;
	env->player->x -= SLIDING_SPEED * env->player->touches_h_wall;
	env->player->y -= SLIDING_SPEED * env->player->touches_v_wall;
	env->player->xc = (int)env->player->x / BLOCKW;
	env->player->yc = (int)env->player->y / BLOCKH;
	env->player->no_rotate = true;
	move_player(player, env);
}

// void	draw_triangle(int size, int x, int y, int color, t_env *env)
// {
// 	int	i;
// 	int	start_x;
// 	int	end_x;
// 	int	height;
// 	int	j;

// 	i = 0;
// 	start_x = 0;
// 	end_x = 0;
// 	height = 0;
// 	j = 0;
// 	y = y - size / 2;
// 	height = (int)(size * sin((80) * PI / 180.0));
// 	while (i < height)
// 	{
// 		start_x = x - (i * size) / height / 2;
// 		end_x = x + (i * size) / height / 2;
// 		j = start_x;
// 		while (j <= end_x)
// 		{
// 			mm_pixel_put(j, y + i, color, env);
// 			j++;
// 		}
// 		i++;
// 	}
// }
