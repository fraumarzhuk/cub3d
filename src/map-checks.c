/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariannazhukova <mariannazhukova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:19:36 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/07 15:14:57 by mariannazhu      ###   ########.fr       */
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
	int		x;

	x = 0;
	while (is_space(map_copy[0][x]))
		x++;
	explore_borders(map_copy, data, x); // save x first point, where the loop stops	
}

void explore_borders(char **map_copy, t_data *data, int x)
{

	int y;

	y = 0;
	//down
	while ((map_copy[y]))
	{
		while (map_copy[y][x])
		{
			if (!is_valid_x(map_copy, x, y))
				error_and_exit("Incorrect walls!");
			if (map_copy[y][x + 1] == '1')
				x++;
			else if (map_copy[y + 1][x] && map_copy[y + 1][x] == '1')
				y++;
			else if (x > 0 && map_copy[y][x - 1] == '1')
				x--;
			else 
				break ;

		}
	}
	//up
	y = data->map_lines - 1;
	x = ft_strlen(map_copy[y]) - 1;
	while (map_copy[y][x])
	{
		if (!is_valid_x(map_copy, x, y))
				error_and_exit("Incorrect walls!");
		if (y + 1 < data->map_lines && map_copy[y + 1][x] == '1')
				y++;
		else if (y > 0 && map_copy[y - 1][x] == '1')
				y--;
		else if (x > 0 && map_copy[y][x - 1] == '1')
				x--;
		else if (map_copy[y][x + 1] == '1')
				x++;
		else
			break ;
	}
	
}
int is_valid_x(char **map_copy, int x, int y)
{
	// return ((y > 0 && map_copy[y - 1][x] && map_copy[y - 1][x] != '1') &&
	// 		(map_copy[y][x + 1] && map_copy[y][x + 1] != '1') &&
	// 		(x > 0 && map_copy[y][x - 1] && map_copy[y][x - 1] != '1'));
	if ((y > 0 && map_copy[y - 1][x] && map_copy[y - 1][x] != '1') &&
			(map_copy[y][x + 1] && map_copy[y][x + 1] != '1') &&
			(x > 0 && map_copy[y][x - 1] && map_copy[y][x - 1] != '1'))
			{
				return (0);
			}
	printf("Cur line: %s\n", map_copy[y]);
	return (1);
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