/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:02:14 by mzhukova          #+#    #+#             */
/*   Updated: 2024/09/27 11:12:10 by mzhukova         ###   ########.fr       */
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
	save_textures(map, env->data);
	return (1);
}

void map_validation(char *argv, t_env *env)
{
	char	*res;

	res = &argv[(int)ft_strlen(argv) - 4];
	if (ft_strncmp(res, ".cub", 4))
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
	else if (ft_strlen(new_node->line) > 1)
		new_node->line[ft_strlen(new_node->line)] = '\0';
	return (1);
}

void save_textures(t_map *map, t_data *data)
{
	t_map *temp;

	temp = map;
	while (temp)
	{
		if (!(ft_strncmp(temp->line, "NO", 2)))
			data->north = temp->line + 3;
		else if (!(ft_strncmp(temp->line, "SO", 2)))
			data->south = temp->line + 3;
		else if (!(ft_strncmp(temp->line, "WE", 2)))
			data->west = temp->line + 3;
		else if (!(ft_strncmp(temp->line, "EA", 2)))
			data->east = temp->line + 3;
		else if (temp->line[0] == 'F' || temp->line[0] == 'C')
				save_floor_and_ceiling(temp->line, data);
		else if (temp->line[0] == '1')
			break ;
		temp = temp->next;
	}
}

void	save_floor_and_ceiling(char *line, t_data *data)
{
	
	if (ft_strchr(line, ','))
	{
		if (line[0] == 'F')
			data->floor = save_rgb(line);
		else if (line[0] == 'C')
			data->ceiling = save_rgb(line);
	}
	else
	{
		if (line[0] == 'F')
			data->pic_floor = line + 3;
		else if (line[0] == 'C')
			data->pic_ceiling = line + 3;
	}
}

t_rgb *save_rgb(char *line)
{
	char **res;
	t_rgb *rgb;

	rgb = (t_rgb *)ft_malloc(sizeof(t_rgb));
	res = ft_split(line, ',');
	if (!rgb || !res)
		error_and_exit("Malloc failed!");
	rgb->r = ft_atoi(ft_strdup(res[0]));
	rgb->g = ft_atoi(ft_strdup(res[1]));
	rgb->b = ft_atoi(ft_strdup(res[2]));
	free_split(res);
	
	return (rgb);
}
// while temp->line[0] != '1'
	//temp->parsed_line = ft_split(temp->line, " ");