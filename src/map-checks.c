/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:19:36 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/02 13:03:07 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

//check for characters
//is last(inside map_checks()
//check walls

void map_checks(char **map_copy) //pass data->map_copy
{
	int	i;

	i = 0;
	while (map_copy[i])
	{
		invalid_char_check(map_copy[i]);
		i++;
	}
}

int invalid_char_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]) && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != '0' && line[i] != '1')
			error_and_exit("Incorrect characters inside map!");
		i++;
	}
	return (1);
}


