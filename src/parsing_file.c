/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:56:59 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/02 09:49:10 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void file_validation(char *argv, t_env *env)
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
	new_node->prev = curr;
	new_node->line = get_next_line(data->fd);
    if (!new_node->line)
        return (0);
	else if (ft_strlen(new_node->line) > 1 && new_node->line[ft_strlen(new_node->line) - 1] == '\n')
		new_node->line[ft_strlen(new_node->line) - 1] = '\0';
	return (1);
}

void save_textures(t_map *map, t_data *data)
{
	t_map *temp;
	
	while (map && map->line)
	{
		if (!(ft_strncmp(map->line, "NO", 2)))
			data->north = map->line + 3;
		else if (!(ft_strncmp(map->line, "SO", 2)))
			data->south = map->line + 3;
		else if (!(ft_strncmp(map->line, "WE", 2)))
			data->west = map->line + 3;
		else if (!(ft_strncmp(map->line, "EA", 2)))
			data->east = map->line + 3;
		else if (map->line[0] == 'F' || map->line[0] == 'C')
				save_floor_and_ceiling(map->line, data);
		else if (is_map_line(map->line))
			break ;
		map = map->next;
	}
	temp = map;
	while (temp && temp->line)
	{
		data->map_lines++;
		if (is_map_line(temp->line))
			temp->is_map = true;
		temp = temp->next;
	}
}

// void get_texture(char *line, char *p_name)
// {
// 	char *texture;
// 	texture = 
// }

void	save_floor_and_ceiling(char *line, t_data *data)
{
	
	if (ft_strchr(line, ','))
	{
		if (line[0] == 'F')
			data->floor = save_rgb(&line[2]);
		else if (line[0] == 'C')
			data->ceiling = save_rgb(&line[2]);
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

//TODO:
//1. Map is the last check
//2. Skip spaces before and between textures and rgb