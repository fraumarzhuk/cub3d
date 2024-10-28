/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:05:47 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/28 16:55:00 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

float new_angle(float angle, float angle_speed, bool left, bool right)
{
	if (left)
		angle -= angle_speed;
	if (right)
		angle += angle_speed;
	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return angle;
}

void move_player(t_player *player, t_env *env)
{


	double next_x = player->x;
	double next_y = player->y;
	float angle_speed = 0.5;
	// float cos_angle = cos(player->angle);
	// float sin_angle = sin(player->angle);
	player->angle = new_angle(player->angle, angle_speed, player->left_rotate, player->right_rotate);
	
	if (player->key_up && player->y - SPEED >= 0)
	{
		get_new_pos2(&next_x, &next_y, player->angle, SPEED);
		// next_x -= cos_angle * SPEED;
		// next_y -= sin_angle * SPEED;
		
	}
	if (player->key_down && player->y + SPEED < HEIGHT)
	{
		get_new_pos2(&next_x, &next_y, player->angle + 180, SPEED);
		// next_x += cos_angle * SPEED;
        // next_y += sin_angle * SPEED;
	}
	if (player->key_left && player->x - SPEED >= 0)
	{
		get_new_pos2(&next_x, &next_y, player->angle - 90, SPEED);
		// next_x -= sin_angle * SPEED;
        // next_y += cos_angle * SPEED;
	}
	if (player->key_right && player->x + SPEED < WIDTH)
	{
		get_new_pos2(&next_x, &next_y, player->angle + 90, SPEED);
		// next_x += sin_angle * SPEED;
        // next_y -= cos_angle * speed;
	}
	
	int next_matrix_x = next_x / BLOCKW;
	int next_matrix_y = next_y / BLOCKH;

	if (env->data->map_copy[next_matrix_y][next_matrix_x] != '1')
	{
		player->x = next_x;
		player->y = next_y;
		player->xc = next_matrix_x;
		player->yc = next_matrix_y;
	}
}

/* void	get_new_pos2(double *pos, double dir[2], double dist, double *new_pos) */


void clear_image(t_env *env)
{
    for(int y = 0; y < HEIGHT; y++)
        for(int x = 0; x < WIDTH; x++)
            my_pixel_put(x, y, 0, env);
}

int draw_loop(t_env *env)
{
	t_player *player = env->player;
	move_player(player, env);
	clear_image(env);
	draw_square(mini_m_w/2, mini_m_h/2, mini_p, 0x00FF00, env);
	// draw_triangle(mini_p, mini_m_w/2, mini_m_h /2, 0x00FF00, env);
	draw_map(env);
	draw_mini_border(env);
	// float ray_x = player->x;
	// float ray_y = player->y;
	// while (!touch(ray_x, ray_y, env))
	// {
	// 	// printf("Ray x %f, ray y: %f\n", )
	// 	my_pixel_put(ray_x, ray_y, MINI_BORDER_C, env);
	// 	ray_x += player->angle;
	// 	ray_y += player->angle;
	// }
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img->img, 0, 0);
	return (1);
}

bool touch(float px, float py, t_env *env)
{
    int x = px / BLOCKW;
    int y = py / BLOCKH;
    if(env->data->map_copy[y][x] == '1')
        return true;
    return false;
}


void	draw_triangle(int size, int x, int y, int color, t_env *env)
{
	int	i;
	int	start_x;
	int	end_x;
	int	height;
	int	j;

	i = 0;
	start_x = 0;
	end_x = 0;
	height = 0;
	j = 0;
	y = y - size / 2;
	height = (int)(size * sin((80) * PI / 180.0));
	while (i < height)
	{
		start_x = x - (i * size) / height / 2;
		end_x = x + (i * size) / height / 2;
		j = start_x;
		while (j <= end_x)
		{
			my_pixel_put(j, y + i, color, env);
			j++;
		}
		i++;
	}
}