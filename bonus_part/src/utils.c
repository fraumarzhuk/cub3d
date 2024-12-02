/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:06:32 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/12 17:56:18 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	error_and_exit(char *str)
{
	printf("%s\n", str);
	ft_destructor();
	exit(1);
}

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
	env->data->true_lines = 0;
	env->data->map_lines = 0;
	env->data->map_len = 0;
	env->data->ceiling = NULL;
	env->data->pic_ceiling = NULL;
	env->data->pic_floor = NULL;
	env->data->floor = NULL;
	env->data->north = NULL;
	env->data->south = NULL;
	env->data->west = NULL;
	env->data->east = NULL;
	env->data->enjoyer = NULL;
	env->data->beer = NULL;
	env->data->brezel = NULL;
	env->data->brezel_shop = NULL;
	env->data->beer_shop = NULL;
	env->data->pfand = NULL;
	env->data->pfandautomat = NULL;
	env->data->pfand_amount = 0;
	env->data->pfand_collected = 0;
	init_player(env->player);
	init_textures(env);
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
	player->counter = 0;
	player->mm_p_height = (int)(MINI_P * sin((80) * PI / 180.0));
	player->player_pos = HANDS;
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
	// env->player_pic = (t_img *)ft_malloc(sizeof(t_img));
	env->beer_shop = (t_img *)ft_malloc(sizeof(t_img));
	env->brezel_shop = (t_img *)ft_malloc(sizeof(t_img));
	env->pfand = (t_img *)ft_malloc(sizeof(t_img));
	env->pfandautomat = (t_img *)ft_malloc(sizeof(t_img));
}

void	copy_spaces(char *map_line, char *new_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map_line[i])
	{
		if (map_line[i] == '\t')
		{
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
		}
		else
			new_line[j++] = map_line[i];
		i++;
	}
	new_line[j++] = '\0';
}

// void	check_parsed_data(t_env *env, t_map *map)
// {
// 	printf("PARSED MAP FROM LINKED LIST:\n\n");
// 	t_map *temp;
// 	temp = map;
// 	while (temp)
// 	{
// 		printf("%s\n", temp->line);
// 		temp = temp->next;
// 	}
// 	printf("**************************\n");
// 	printf("PARSED MAP FROM 2D array:\n\n");
// 	int i = 0;
// 	while (env->data->map_copy[i])
// 	{
// 		printf("%s\n", env->data->map_copy[i]);
// 		i++;
// 	}
// 	printf("**************************\n");
// 	printf("PARSED TEXTURES:\n\n");
// 	printf("NO: %s\n", env->data->north);
// 	printf("SO: %s\n", env->data->south);
// 	printf("WE: %s\n", env->data->east);
// 	printf("EA: %s\n", env->data->west);
// 	if (env->data->pic_ceiling && env->data->pic_floor)
// 	{
// 		printf("WE: %s\n", env->data->pic_ceiling);
// 		printf("EA: %s\n", env->data->pic_floor);
// 	}
// 	printf("**************************\n");
// 	if (env->data->ceiling && env->data->floor)
// 	{		
// 		printf("RGB TEXTURES (F and C):\n\n");
// 		printf("floor rgb: \e[1;31m %d\e[0m, \e[1;32m%d\e[0m, \e[1;34m%d\e[0m\n", env->data->floor->r,
// 				env->data->floor->g, env->data->floor->b);
// 		printf("ceiling rgb: \e[1;31m %d\e[0m, \e[1;32m%d\e[0m, \e[1;34m%d\e[0m\n", env->data->ceiling->r,
// 				env->data->ceiling->g, env->data->ceiling->b);
// 	}
// 	printf("map_lines: %d\n", env->data->true_lines);
// }