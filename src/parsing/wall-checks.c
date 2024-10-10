/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall-checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:09:30 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/10 17:21:22 by mzhukova         ###   ########.fr       */
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
		x = 1;
		while (map_copy[y][x])
		{
			if (is_space(map_copy[y][x]))
			{
				if (y == 0 && !is_wall_or_space(map_copy[y + 1][x]))
					error_and_exit("Incorrect_wall1!");
				else if ((y > 0 && !is_wall_or_space(map_copy[y - 1][x])) || (y + 1 < data->map_lines && !is_wall_or_space(map_copy[y + 1][x])))
				{
					printf("vertical. x: %d, y: %d\n", x, y);
					error_and_exit("Incorrect_wall2!");
				}
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
				error_and_exit("Incorrect_wall3!");
		}
		x++;
	}
}

int	is_wall_or_space(char c)
{
	return (c == '1' || is_space(c));
}
