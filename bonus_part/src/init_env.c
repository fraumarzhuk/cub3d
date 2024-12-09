/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:08:50 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/09 16:57:15 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	init_env(t_env *env)
{
	env->data = (t_data *)ft_malloc(sizeof(t_data));
	env->data->ceiling = (t_rgb *)ft_malloc(sizeof(t_rgb));
	env->ceiling = (t_img *)ft_malloc(sizeof(t_img));
	env->floor = (t_img *)ft_malloc(sizeof(t_img));
	env->data->floor = (t_rgb *)ft_malloc(sizeof(t_rgb));
	env->mini_map = (t_img *)ft_malloc(sizeof(t_img));
	env->canvas = (t_img *)ft_malloc(sizeof(t_img));
	env->scene_canvas = (t_img *)ft_malloc(sizeof(t_img));
	env->player = (t_player *)ft_malloc(sizeof(t_player));
	env->textures_loaded = false;
	init_data(env->data);
	init_player(env->player);
	init_textures(env);
}

void	init_data(t_data *data)
{
	data->true_lines = 0;
	data->map_lines = 0;
	data->map_len = 0;
	data->ceiling = NULL;
	data->pic_ceiling = NULL;
	data->pic_floor = NULL;
	data->floor = NULL;
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->enjoyer = NULL;
	data->beer = NULL;
	data->brezel = NULL;
	data->brezel_shop = NULL;
	data->beer_shop = NULL;
	data->pfand = NULL;
	data->pfandautomat = NULL;
	data->loading_screen = NULL;
	data->pfandbon = NULL;
	data->rules = NULL;
	data->pfand_amount = 0;
	data->pfand_collected = 0;
}

void	init_player2(t_player *player)
{
	player->player_pos = HANDS;
	player->display_rules = false;
	player->mouse_on = false;
	player->no_rotate = false;
	player->p_x = 0;
	player->p_y = 0;
}

void	init_player(t_player *player)
{
	player->x = MINI_M_SIZE / 2;
	player->y = MINI_M_SIZE / 2;
	player->dir_x = player->x;
	player->dir_y = player->y;
	player->plane_x = 0;
	player->plane_y = 0.66;
	player->orientation = 0;
	player->sprite = NULL;
	player->angle = -90;
	player->key_right = false;
	player->key_left = false;
	player->key_down = false;
	player->key_up = false;
	player->right_rotate = false;
	player->left_rotate = false;
	player->render_move = true;
	player->display_bon = false;
	player->counter = 0;
	player->pfand_sum = 0;
	player->mm_p_height = (int)(MINI_P * sin((80) * PI / 180.0));
	init_player2(player);
}

void	init_textures(t_env *env)
{
	env->floor = (t_img *)ft_malloc(sizeof(t_img));
	env->ceiling = (t_img *)ft_malloc(sizeof(t_img));
	env->north_wall = (t_img *)ft_malloc(sizeof(t_img));
	env->south_wall = (t_img *)ft_malloc(sizeof(t_img));
	env->east_wall = (t_img *)ft_malloc(sizeof(t_img));
	env->enjoyer = (t_img *)ft_malloc(sizeof(t_img));
	env->enj_beer = (t_img *)ft_malloc(sizeof(t_img));
	env->enj_brezel = (t_img *)ft_malloc(sizeof(t_img));
	env->west_wall = (t_img *)ft_malloc(sizeof(t_img));
	env->beer_shop = (t_img *)ft_malloc(sizeof(t_img));
	env->brezel_shop = (t_img *)ft_malloc(sizeof(t_img));
	env->pfand = (t_img *)ft_malloc(sizeof(t_img));
	env->pfandautomat = (t_img *)ft_malloc(sizeof(t_img));
	env->loading_screen = (t_img *)ft_malloc(sizeof(t_img));
	env->pfandbon = (t_img *)ft_malloc(sizeof(t_img));
	env->rules = (t_img *)ft_malloc(sizeof(t_img));
}
