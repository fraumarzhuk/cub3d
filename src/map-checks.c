/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:19:36 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/09 11:38:16 by mzhukova         ###   ########.fr       */
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


void check_walls(char **map_copy, t_data *data)
{
	int		y;
	char	*trimmed_line;

	y = 1;
	while (y < data->map_lines)
	{
		trimmed_line = trim_spaces(map_copy[y]);
		skip_h_gap(trimmed_line, y);
		y++;
	}
	scan_vertically(map_copy, data);
}

void scan_vertically(char **map_copy, t_data *data)
{
	int	y;
	int	x;
	
	x = 1;
	y = 1;
	while (y < data->map_lines -1)
	{
		x = 1;
		while (map_copy[y][x])
		{
			if (is_space(map_copy[y][x]))
			{
				if ((!is_space(map_copy[y - 1][x]) || map_copy[y - 1][x] != '1') && 
					(!is_space(map_copy[y + 1][x]) || map_copy[y + 1][x] != '1'))
				{
					printf("vertical. x: %d, y: %d\n", x, y);
					error_and_exit("Incorrect_wall!");
				}
			}
			x++;
		}
		y++;
	}
}

void skip_h_gap(char *map_line, int y)
{
	int	x;

	x = 1;
	while (map_line[x] && (x < (int)ft_strlen(map_line)))
	{
		if(is_space(map_line[x]))
		{
			if ((!is_space(map_line[x - 1]) || map_line[x - 1] != '1') && (!is_space(map_line[x + 1]) || map_line[x + 1] != '1'))
			{
				printf("horizontal. x: %d, y: %d\n", x, y);
				error_and_exit("Incorrect_wall!");
			}
		}	
		x++;
	}
}

void check_parsed_data(t_env *env, t_map *map)
{
	printf("PARSED MAP FROM LINKED LIST:\n\n");
	t_map *temp;
	temp = map;
	while (temp)
	{
		printf("%s\n", temp->line);
		temp = temp->next;
	}
	printf("**************************\n");
	printf("PARSED MAP FROM 2D array:\n\n");
	int i = 0;
	while (env->data->map_copy[i])
	{
		printf("%s\n", env->data->map_copy[i]);
		i++;
	}
	printf("**************************\n");
	printf("PARSED TEXTURES:\n\n");
	printf("NO: %s\n", env->data->north);
	printf("SO: %s\n", env->data->south);
	printf("WE: %s\n", env->data->east);
	printf("EA: %s\n", env->data->west);
	if (env->data->pic_ceiling && env->data->pic_floor)
	{
		printf("WE: %s\n", env->data->pic_ceiling);
		printf("EA: %s\n", env->data->pic_floor);
	}
	printf("**************************\n");
	if (env->data->ceiling && env->data->floor)
	{		
		printf("RGB TEXTURES (F and C):\n\n");
		printf("floor rgb: %d, %d, %d\n", env->data->floor->r, env->data->floor->g, env->data->floor->b);
		printf("ceiling rgb: %d, %d, %d\n", env->data->ceiling->r, env->data->ceiling->g, env->data->ceiling->b);
	}
	printf("map_lines: %d\n", env->data->map_lines);
}