/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:02:14 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/09 17:22:46 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub_bonus.h"

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
	save_map_end(map);
	save_map_copy(env->data, &map);
	map_checks(env->data->map_copy, env);
	find_pfandamount(env->data);
	return (1);
}

void	save_map_end(t_map *map)
{
	t_map	*temp;

	temp = map;
	while (temp && temp->next && temp->line && temp->next->line)
		temp = temp->next;
	while (temp && temp->line && temp->prev && !is_map_line(temp->line))
		temp = temp->prev;
	if (is_map_line(temp->line))
		temp->last_line = true;
}

int	is_map_line(char *line)
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
	if (trimmed_line[len - 1] == '1')
		end = true;
	return (start && end);
}

void	save_map_copy(t_data *data, t_map **map)
{
	int		i;
	t_map	*temp;

	i = 0;
	data->map_copy = (char **)ft_calloc(data->true_lines + 1, sizeof(char *));
	if (!data->map_copy)
		error_and_exit("Malloc failed.");
	while (*map && (*map)->line && !is_map_line((*map)->line))
		*map = (*map)->next;
	temp = *map;
	while (temp && temp->line)
	{
		if (!temp->is_map && !temp->last_line)
			error_and_exit("Empty line in the middle of the map!");
		tabs_to_spaces(temp->line);
		data->map_copy[i] = ft_strdup(temp->line);
		if (temp->last_line)
			break ;
		temp = temp->next;
		i++;
	}
	data->map_copy[++i] = NULL;
	data->map_lines = data->true_lines;
}

void	save_map_lines(t_map *map, t_data *data)
{
	t_map	*temp;

	temp = map;
	while (temp && temp->line)
	{
		data->map_lines++;
		if (is_map_line(temp->line))
		{
			temp->is_map = true;
			data->true_lines++;
		}
		temp = temp->next;
	}
}
