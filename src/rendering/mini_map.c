/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:41:53 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/24 17:19:50 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void init_minimap(t_img *img, t_data *data, t_env *env)
{
	img->img = mlx_xpm_file_to_image(env->mlx, data->pic_floor, &img->width, &img->height);
	if (!img->img)
		error_and_exit("failed to create the img");

	draw_square(WIDTH / 2, HEIGHT / 2, 15, 0x00ff00, env);
}

void draw_map(t_env *env)
{
	// char **map;

	// map = env->data->map_copy;
	int color = 0x0c187c9;
	for (int y = 0; env->data->map_copy[y]; y++)
		for(int x = 0; env->data->map_copy[y][x]; x++)
			if (env->data->map_copy[y][x] == '1')
				draw_square(x * BLOCKW, y * BLOCKH, BLOCKH, color, env);
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