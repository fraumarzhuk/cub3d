/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:41:53 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/25 15:40:04 by mzhukova         ###   ########.fr       */
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

	int player_x_block = env->player->x / BLOCKW;
	int player_y_block = env->player->y / BLOCKH;

	for (int y = 0; env->data->map_copy[y]; y++) {
		for (int x = 0; env->data->map_copy[y][x]; x++) {
			if (env->data->map_copy[y][x] == '1')
			{
				int draw_x = (x - player_x_block + mini_v_w) * BLOCKW;
				int draw_y = (y - player_y_block + mini_v_h) * BLOCKH;
				if (draw_x >= 0 && draw_x < mini_m_w && draw_y >= 0 && draw_y < mini_m_h) {
					draw_square(draw_x, draw_y, BLOCKH, color, env);
				}
			}
		}
	}
}


// void draw_map(t_env *env)
// {
// 	int color = 0x0c187c9;
// 	int y = env->player->yc;
// 	int y_view;
// 	int x_view;
	
// 	y_view = (HEIGHT / 2 - BLOCKH / 2) / BLOCKH;
// 	x_view = (WIDTH / 2 - BLOCKW / 2) / BLOCKW;
// 	printf("x coord: %d, y coord %d\n", env->player->xc, env->player->yc);
// 	printf("x view: %d y view: %d\n", x_view, y_view);
// 	while (env->data->map_copy[y] && y <= y_view)
// 	{
// 		int x = env->player->xc;
// 		while (env->data->map_copy[y][x] && x <= x_view)
// 		{
// 			if (env->data->map_copy[y][x] == '1')
// 				draw_square(x * BLOCKW, y * BLOCKH, BLOCKH, color, env);
// 			x++;
// 		}
// 		y++;
// 	}
// }
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