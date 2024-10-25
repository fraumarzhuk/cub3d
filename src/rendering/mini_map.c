/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:41:53 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/25 16:04:58 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

// void init_minimap(t_img *img, t_data *data, t_env *env)
// {
// 	draw_map(env);
// 	draw_square(WIDTH / 2, HEIGHT / 2, 15, 0x00ff00, env);
// }

// void draw_map(t_env *env)
// {
// 	int color = 0x0c187c9;
// 	for (int y = 0; env->data->map_copy[y]; y++)
// 		for(int x = 0; env->data->map_copy[y][x]; x++)
// 			if (env->data->map_copy[y][x] == '1')
// 				draw_square(x * BLOCKW, y * BLOCKH, BLOCKH, color, env);
// }

void draw_map(t_env *env)
{
	int color = 0x0c187c9;

	int player_x_block = env->player->xc;
	int player_y_block = env->player->yc;
	double player_x_offset = env->player->x - (player_x_block * BLOCKW);
	double player_y_offset = env->player->y - (player_y_block * BLOCKH);
	double player_center_x = (mini_m_w / 2) - player_x_offset;
	double player_center_y = (mini_m_h / 2) - player_y_offset;

	for (int y = 0; env->data->map_copy[y]; y++) {
		for (int x = 0; env->data->map_copy[y][x]; x++) {
			if (env->data->map_copy[y][x] == '1') {
				int draw_x = (x - player_x_block) * BLOCKW + player_center_x;
				int draw_y = (y - player_y_block) * BLOCKH + player_center_y;

				if (draw_x >= 0 && draw_x < mini_m_w && draw_y >= 0 && draw_y < mini_m_h) {
					draw_square(draw_x, draw_y, BLOCKH, color, env);
				}
			}
		}
	}
	draw_square(mini_m_w / 2 - mini_p / 2, mini_m_h / 2 - mini_p / 2, mini_p, 0x00FF00, env);
}


// void render_minimap()
// {
// 	//actual map_height
// 	//actual map_width
// 	//minimap height(how much to render)
// 	//minimap width (how much to render)
// 	//player position (env->player->pos->x)
// 	//mypixelput or structures?

// // ?? get the longest line len from the map; 
// 	//1. create an image on top of window of certain size
// 	//2. make a background of an image
// }


//--render minimap
//-create a player as an triangle
//-- first make key events so it works with the arrow keys, later add mouse movements

//movements:
//if left arrow -- turn left
//if right arrow -- turn right
// N - 0, E - 90, W -90(270?), S - 180