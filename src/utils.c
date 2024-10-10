/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:06:32 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/10 14:33:04 by mzhukova         ###   ########.fr       */
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
	env->data->ceiling = NULL;
	env->data->pic_ceiling = NULL;
	env->data->pic_floor = NULL;
	env->data->floor = NULL;
	env->data->north = NULL;
	env->data->south = NULL;
	env->data->west = NULL;
	env->data->east = NULL;
	//env->data->map_copy = NULL;
}

void check_parsed_data(t_env *env, t_map *map)
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
		printf("floor rgb: %d, %d, %d\n", env->data->floor->r, env->data->floor->g, env->data->floor->b);
		printf("ceiling rgb: %d, %d, %d\n", env->data->ceiling->r, env->data->ceiling->g, env->data->ceiling->b);
	}
	printf("map_lines: %d\n", env->data->true_lines);
}