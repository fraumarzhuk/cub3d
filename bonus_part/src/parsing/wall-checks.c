/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall-checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:09:30 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/05 14:49:57 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	check_walls(char **map_copy, t_data *data)
{
	int		y;
	int		len;
	char	*trimmed_line;

	y = 1;
	len = 0;
	check_first_last_line(map_copy[0]);
	check_first_last_line(map_copy[data->map_lines - 1]);
	while (y < data->map_lines - 1 && map_copy[y])
	{
		trimmed_line = trim_spaces(map_copy[y]);
		len = ft_strlen(trimmed_line);
		if (len > data->map_len)
			data->map_len = len;
		skip_h_gap(trimmed_line);
		y++;
	}
	scan_vertically(map_copy, data);
}

void	scan_vertically(char **map_copy, t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_lines)
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (is_map_char(map_copy[y][x]))
			{
				if (!map_copy[y - 1][x] || !map_copy[y + 1][x])
					error_and_exit("Incorrect wall1!");
				else if (map_copy[y - 1][x] && is_space(map_copy[y - 1][x]))
					error_and_exit("Incorrect wall2!");
				else if (map_copy[y + 1][x] && is_space(map_copy[y + 1][x]))
					error_and_exit("Incorrect wall3!");
			}
			if (is_space(map_copy[y][x]))
				check_vertical(map_copy, y, x);
			x++;
		}
		y++;
	}
}

void	skip_h_gap(char *map_line)
{
	int	x;

	x = 1;
	while (x < (int)ft_strlen(map_line) - 1)
	{
		if (is_space(map_line[x]))
		{
			if ((!is_wall_or_space(map_line[x - 1])
					|| !is_wall_or_space(map_line[x + 1])))
				error_and_exit("Incorrect_wall5!");
		}
		x++;
	}
}

void	check_vertical(char **map_copy, int y, int x)
{
	if ((map_copy[y][x] && map_copy[y][x] == '1'))
	{
		if (map_copy[y - 1][x] && !is_wall_or_space(map_copy[y - 1][x]))
			error_and_exit("Incorrect wall3!");
		if (map_copy[y + 1][x] && !is_wall_or_space(map_copy[y + 1][x]))
			error_and_exit("Incorrect wall4!");
	}
}

void	save_wall_textures(char *map_line, t_data *data)
{
	if (!(ft_strncmp(map_line, "NO", 2)))
		data->north = get_texture(map_line, "NO", false);
	else if (!(ft_strncmp(map_line, "SO", 2)))
		data->south = get_texture(map_line, "SO", false);
	else if (!(ft_strncmp(map_line, "WE", 2)))
		data->west = get_texture(map_line, "WE", false);
	else if (!(ft_strncmp(map_line, "EA", 2)))
		data->east = get_texture(map_line, "EA", false);
}
