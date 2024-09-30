/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:02:14 by mzhukova          #+#    #+#             */
/*   Updated: 2024/09/30 13:38:13 by mzhukova         ###   ########.fr       */
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
	save_map_copy(env->data, map);
	// print_parsed_data(map, env->data);
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
		else if ((map->line[0] == '1' || is_space(map->line[0])) && is_map_line(map->line))
			break ;
		map = map->next;
	}
	temp = map;
	while (temp && temp->line && ft_strchr(temp->line, '1'))
	{
		data->map_lines++;
		temp = temp->next;
	}
}

int is_map_line(char *line)
{
	char	*trimmed_line;
	int		len;
	bool	start;
	bool	end;
	
	start = false;
	end = false;
	trimmed_line = trim_spaces(line);
	if (trimmed_line[0] == '1')
			start = true;
	len = ft_strlen(trimmed_line);
	while (len > 0 && is_space(trimmed_line[len - 1]))
		len--;	
	if (trimmed_line[len - 1] == '1')
			end = true;	
	return (start && end);
}

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

void save_map_copy(t_data *data, t_map *map)
{
	int	i;
	
	i = 0;
	data->map_copy = (char **)ft_calloc(((sizeof(char *) * (data->map_lines) + 1)), 1);
	if (!data->map_copy)
		error_and_exit("Malloc failed.");
	while (map && map->line && !is_map_line(map->line))
		map = map->next;
	while (map && map->line && i <= data->map_lines)
	{
		data->map_copy[i] = ft_strdup(map->line);
		printf("%s\n", data->map_copy[i]);
		map = map->next;
		i++;
	}
	data->map_copy[i] = NULL;
}


//TODO:
//1. run check walls and other checks on copy of 2d map_copy;