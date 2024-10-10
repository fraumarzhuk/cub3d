/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:19:36 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/10 16:05:41 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	map_checks(char **map_copy, t_env *env) //pass data->map_copy
{
	int	i;

	i = 0;
	while (map_copy[i])
	{
		invalid_char_check(map_copy[i], env->player);
		i++;
	}
	check_walls(map_copy, env->data);
	check_rgb(env->data);
	if (!env->player->orientation)
		error_and_exit("No player found.");
}

int	invalid_char_check(char *line, t_player *player)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (!player->orientation)
				player->orientation = line[i];
			else
				error_and_exit("Too many players.");
		}
		if (!is_space(line[i]) && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != '0' && line[i] != '1')
			error_and_exit("Incorrect characters inside map!");
		i++;
	}
	return (1);
}

void	check_first_last_line(char *map_line)
{
	int	x;

	x = 0;
	while (map_line && map_line[x])
	{
		if (!is_wall_or_space(map_line[x]))
			error_and_exit("Incorrect wall!");
		x++;
	}
}

void	check_rgb(t_data *data)
{
	if ((!data->ceiling || !data->floor)
		&& (!data->pic_ceiling || !data->pic_floor))
		error_and_exit("No textures saved or map is not in the end.");
	if (!data->pic_ceiling)
	{
		if (data->ceiling->r < 0 || data->ceiling->g < 0 || data->ceiling->b < 0
			|| data->ceiling->r > 255 || data->ceiling->g > 255
			|| data->ceiling->b > 255)
			error_and_exit("No correct data for ceiling provided.");
	}
	if (!data->pic_floor)
	{
		if (data->floor->r < 0 || data->floor->g < 0 || data->floor->b < 0
			|| data->floor->r > 255 || data->floor->g > 255
			|| data->floor->b > 255)
			error_and_exit("No correct data for floor provided.");
	}
}
