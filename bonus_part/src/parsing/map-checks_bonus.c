/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-checks_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:19:36 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/09 17:22:31 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub_bonus.h"

void	map_checks(char **map_copy, t_env *env) //pass data->map_copy
{
	int	i;

	i = 0;
	while (map_copy[i])
	{
		invalid_char_check(map_copy[i], env->player, i);
		i++;
	}
	if (!env->data->east || !env->data->north
		||!env->data->west || !env->data->south)
		error_and_exit("No wall textures saved!");
	check_walls(map_copy, env->data);
	check_rgb(env->data);
	if (!env->player->orientation)
		error_and_exit("No player found.");
}

int	invalid_char_check(char *line, t_player *player, int y)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (!player->orientation)
				set_player_pos(player, i, y, line[i]);
			else
				error_and_exit("Too many players.");
		}
		if (!is_space(line[i]) && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != '0' && line[i] != '1'
			&& line[i] != 'A' && line[i] != 'M'
			&& line[i] != 'B' && line[i] != 'P')
			error_and_exit("Incorrect character inside map!");
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
			error_and_exit("Incorrect wall1!");
		x++;
	}
}

void	check_rgb(t_data *data)
{
	if ((!data->ceiling && !data->floor)
		&& (!data->pic_ceiling && !data->pic_floor))
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
