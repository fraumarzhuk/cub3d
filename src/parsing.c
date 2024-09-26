/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:02:14 by mzhukova          #+#    #+#             */
/*   Updated: 2024/09/26 18:39:53 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	map_init(t_env *env)
{
	t_map	*map;
	
	env->data->line_count = 0;
	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		error_and_exit("Malloc failed...");
	map->line = get_next_line(env->data->fd);
	if (!map->line)
		error_and_exit("Empty map!");
	env->data->line_count++;
	map->next = NULL;
	while (parse_line(&map, env->data))
		env->data->line_count++;
	return (1);
}

void map_validation(char *argv, t_env *env)
{
	char	*res;

	res = &argv[(int)ft_strlen(argv) - 4];
	if (ft_strncmp(res, ".cub", 4) != 0)
		error_and_exit("Incorrect map format!");
	env->data->fd = open(argv, O_RDONLY);
	if (env->data->fd < 0 || read(env->data->fd, 0, 0) < 0)
		error_and_exit("Error reading a file.");
	map_init(env);
}

int	parse_line(t_map **map, t_data *data)
{
	t_map	*new_node;
	t_map	*curr;

	curr = *map;
	new_node = ft_calloc(sizeof(t_map), 1);
	if (!new_node)
		error_and_exit("Malloc failed!");
	new_node->next = NULL;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
	new_node->line = get_next_line(data->fd);
	if (!new_node->line)
		return (0);
	return (1);
}