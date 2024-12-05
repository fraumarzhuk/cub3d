/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:24:08 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/05 14:38:48 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int	is_wall_or_space(char c)
{
	return (c == '1' || c == 'B' || c == 'M' || c == 'A' || is_space(c));
}

int	is_wall_mm(char c)
{
	return (c == '1' || c == 'B' || c == 'M' || c == 'A');
}

int	is_map_char(char c)
{
	return (c == '0' || c == 'N' || c == 'W'
		|| c == 'E' || c == 'S' || c == 'P');
}

void	tabs_to_spaces(char *map_line)
{
	int		tab_count;
	char	*new_line;
	int		i;

	tab_count = 0;
	i = 0;
	while (map_line[i])
	{
		if (map_line[i] == '\t')
			tab_count++;
		i++;
	}
	new_line = ft_malloc(i + tab_count * 3 + 1);
	if (!new_line)
		error_and_exit("Memory allocation failed.");
	copy_spaces(map_line, new_line);
	map_line = ft_strdup(new_line);
	ft_free(new_line);
}

void	check_rgb_num(char *str)
{
	int	i;

	i = 0;
	str = trim_spaces(str);
	if (!str || ft_strlen(str) > 3)
		error_and_exit("Incorrect rgb values");
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !is_space(str[i]))
			error_and_exit("Incorrect rgb values1");
		i++;
	}
}
