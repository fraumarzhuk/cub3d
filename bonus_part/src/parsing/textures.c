/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:33:23 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/11 13:00:42 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	save_textures(t_map *map, t_data *data)
{
	int	map_detected;

	map_detected = 0;
	while (map && map->line)
	{
		if (is_map_line(map->line))
			break ;
		map->line = trim_spaces(map->line);
		choose_texture(map->line, data, map_detected);
		map = map->next;
	}
	save_map_lines(map, data);
	map_detected = 1;
}

void	choose_texture(char *map_line, t_data *data, int map_detected)
{
	if (map_detected == 1)
		error_and_exit("Map_first!");
	if (!(ft_strncmp(map_line, "NO", 2)))
		data->north = get_texture(map_line, "NO", false);
	else if (!(ft_strncmp(map_line, "SO", 2)))
		data->south = get_texture(map_line, "SO", false);
	else if (!(ft_strncmp(map_line, "WE", 2)))
		data->west = get_texture(map_line, "WE", false);
	else if (!(ft_strncmp(map_line, "EA", 2)))
		data->east = get_texture(map_line, "EA", false);
	else if (map_line[0] == 'F' || map_line[0] == 'C')
		save_floor_and_ceiling(map_line, data);
}

char	*get_texture(char *line, char *p_name, bool is_rgb)
{
	char	*texture;
	int		fd;

	texture = line;
	if (ft_strlen(p_name) == 2)
		texture += 2;
	else
		texture++;
	if (!is_space(texture[0]))
		error_and_exit("Incorrect texture format");
	texture = trim_spaces(texture);
	if (!texture)
		error_and_exit("Incorrect map!");
	fd = open(texture, O_RDONLY);
	if (!is_rgb && (fd < 0 || read(fd, 0, 0) < 0))
		error_and_exit("Incorrect texture provided");
	return (texture);
}

void	save_floor_and_ceiling(char *line, t_data *data)
{
	if (ft_strchr(line, ','))
	{
		if (line[0] == 'F')
			data->floor = save_rgb(get_texture(line, "F", true));
		else if (line[0] == 'C')
			data->ceiling = save_rgb(get_texture(line, "C", true));
	}
	else
	{
		if (line[0] == 'F')
			data->pic_floor = get_texture(line, "F", false);
		else if (line[0] == 'C')
			data->pic_ceiling = get_texture(line, "F", false);
	}
}

t_rgb	*save_rgb(char *line)
{
	char	**res;
	t_rgb	*rgb;

	rgb = (t_rgb *)ft_malloc(sizeof(t_rgb));
	res = ft_split(line, ',');
	if (!rgb || !res)
		error_and_exit("Malloc failed!");
	check_rgb_num(res[0]);
	rgb->r = ft_atoi(trim_spaces(res[0]));
	check_rgb_num(res[1]);
	rgb->g = ft_atoi(trim_spaces(res[1]));
	check_rgb_num(res[2]);
	rgb->b = ft_atoi(trim_spaces(res[2]));
	free_split(res);
	return (rgb);
}
