/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:06:32 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/25 12:03:04 by mzhukova         ###   ########.fr       */
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
	env->data->floor = (t_rgb *)ft_malloc(sizeof(t_rgb));
	env->img = (t_img *)ft_malloc(sizeof(t_img));
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
	init_player(env->player);
}

void init_player(t_player *player)
{	
	player->x = WIDTH /2;
	player->y = HEIGHT /2;
	player->orientation = 0;
	player->sprite = NULL;	
}

void copy_spaces(char *map_line, char *new_line)
{
	int i;
	int j;
	
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

void	check_parsed_data(t_env *env, t_map *map)
{
	printf("PARSED MAP FROM LINKED LIST:\n\n");
	t_map *temp;
	temp = map;
	while (temp)
	{
		printf("%s\n", temp->line);
		temp = temp->next;
	}
	printf("**************************\n");
	printf("PARSED MAP FROM 2D array:\n\n");
	int i = 0;
	while (env->data->map_copy[i])
	{
		printf("%s\n", env->data->map_copy[i]);
		i++;
	}
	printf("**************************\n");
	printf("PARSED TEXTURES:\n\n");
	printf("NO: %s\n", env->data->north);
	printf("SO: %s\n", env->data->south);
	printf("WE: %s\n", env->data->east);
	printf("EA: %s\n", env->data->west);
	if (env->data->pic_ceiling && env->data->pic_floor)
	{
		printf("WE: %s\n", env->data->pic_ceiling);
		printf("EA: %s\n", env->data->pic_floor);
	}
	printf("**************************\n");
	if (env->data->ceiling && env->data->floor)
	{		
		printf("RGB TEXTURES (F and C):\n\n");
		printf("floor rgb: \e[1;31m %d\e[0m, \e[1;32m%d\e[0m, \e[1;34m%d\e[0m\n", env->data->floor->r,
				env->data->floor->g, env->data->floor->b);
		printf("ceiling rgb: \e[1;31m %d\e[0m, \e[1;32m%d\e[0m, \e[1;34m%d\e[0m\n", env->data->ceiling->r,
				env->data->ceiling->g, env->data->ceiling->b);
	}
	printf("map_lines: %d\n", env->data->true_lines);
}