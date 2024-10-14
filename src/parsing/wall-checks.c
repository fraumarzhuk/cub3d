/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall-checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:09:30 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/14 19:03:49 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	check_walls(char **map_copy, t_data *data)
{
	int		y;
	char	*trimmed_line;

	y = 1;
	check_first_last_line(map_copy[0]);
	check_first_last_line(map_copy[data->map_lines - 1]);
	while (y < data->map_lines - 1 && map_copy[y])
	{
		trimmed_line = trim_spaces(map_copy[y]);
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
			check_lonely_zero(map_copy, x, y);
			if (is_space(map_copy[y][x]))
			{
				if (y == 0 && !is_wall_or_space(map_copy[y + 1][x]))
					error_and_exit("Incorrect_wall!");
				check_vertical(map_copy, y, x);

			}
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
				error_and_exit("Incorrect_wall!");
		}
		x++;
	}
}

int	is_wall_or_space(char c)
{
	return (c == '1' || is_space(c));
}

int is_map_char(char c)
{
	return (c == '0' || c == 'N' || c == 'W' || c == 'E' || c == 's');
}

void check_lonely_zero(char **map_copy, int x, int y)
{
	if (is_map_char(map_copy[y][x]))
	{
		if (!map_copy[y - 1][x] || !map_copy[y + 1][x])
			error_and_exit("Incorrect wall");
	}
}
void check_vertical(char **map_copy, int y, int x)
{

	if ((map_copy[y][x] && map_copy[y][x] == '1'))
	{
		if (map_copy[y - 1][x] && !is_wall_or_space(map_copy[y - 1][x]))
			error_and_exit("Incorrect wall!");
		if (map_copy[y + 1][x] && !is_wall_or_space(map_copy[y + 1][x]))
			error_and_exit("Incorrect wall!");
	}
}