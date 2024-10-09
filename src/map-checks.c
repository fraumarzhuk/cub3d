/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:19:36 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/09 13:42:29 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

//map_first! maybe just a check for first a last char of trimmed line and maybe next line
//is last(inside map_checks()
//check walls

void map_checks(char **map_copy, t_data *data) //pass data->map_copy
{
	int	i;

	i = 0;
	(void) data;
	while (map_copy[i])
	{
		invalid_char_check(map_copy[i]);
		i++;
	}
	check_walls(map_copy, data);
	check_rgb(data);
}

int invalid_char_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]) && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != '0' && line[i] != '1')
		{
			//printf("char: %c\n", line[i]);
			error_and_exit("Incorrect characters inside map!");
		}
		i++;
	}
	return (1);
}


void check_first_last_line(char *map_line)
{
	int x;

	x = 0;
	while (map_line[x])
	{
		if (!is_wall_or_space(map_line[x]))
			error_and_exit("Incorrect wall!");
		x++;
	}
}
void check_rgb(t_data *data)
{
	if ((data->ceiling->r < 0 || data->ceiling->g < 0 || data->ceiling->b < 0 || data->ceiling->r > 255 || data->ceiling->g > 255 || data->ceiling->b > 255) && !data->pic_ceiling)
		error_and_exit("No correct data for ceiling provided.");
	if ((data->floor->r < 0 || data->floor->g < 0 || data->floor->b < 0 || data->floor->r > 255 || data->floor->g > 255 || data->floor->b > 255) && !data->pic_floor)
		error_and_exit("No correct data for floor provided.");
	if (data->ceiling->r > 255 || data->ceiling->g > 255 || data->ceiling->b > 255)
		error_and_exit("Incorrect RGB colors for ceiling.");
	if (data->floor->r > 255 || data->floor->g > 255 || data->floor->b > 255)
		error_and_exit("Incorrect RGB colors for floor.");
}