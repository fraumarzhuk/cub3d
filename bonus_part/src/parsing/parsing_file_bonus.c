/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:56:59 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/09 17:22:41 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub_bonus.h"

void	file_validation(char *argv, t_env *env)
{
	char	*res;

	res = &argv[(int)ft_strlen(argv) - 4];
	if (ft_strncmp(res, ".cub", 4))
		error_and_exit("Incorrect map format!");
	env->data->fd = open(argv, O_RDONLY);
	if (env->data->fd < 0 || read(env->data->fd, 0, 0) < 0)
		error_and_exit("Error reading a file.");
	map_init(env);
}

int	parse_line(t_map **map, t_data *data)
{
	t_map	*new_node;
	t_map	*curr;

	curr = *map;
	new_node = ft_calloc(sizeof(t_map), 1);
	if (!new_node)
		error_and_exit("Malloc failed!");
	new_node->next = NULL;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
	new_node->prev = curr;
	new_node->line = get_next_line(data->fd);
	if (!new_node->line)
		return (0);
	else if (ft_strlen(new_node->line) > 1
		&& new_node->line[ft_strlen(new_node->line) - 1] == '\n')
		new_node->line[ft_strlen(new_node->line) - 1] = '\0';
	return (1);
}

void	set_player_pos(t_player *player, int x, int y, char orient)
{
	player->orientation = orient;
	if (orient == 'N')
		player->angle = -90;
	else if (orient == 'S')
		player->angle = 90;
	else if (orient == 'E')
		player->angle = 0;
	else if (orient == 'W')
		player->angle = 180;
	player->xc = x;
	player->yc = y;
	player->x = (player->xc + 0.5) * BLOCKW;
	player->y = (player->yc + 0.5) * BLOCKH;
}
