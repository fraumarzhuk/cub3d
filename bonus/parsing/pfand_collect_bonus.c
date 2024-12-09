/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfand_collect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:31:01 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/09 17:22:57 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub_bonus.h"

void	find_pfandamount(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map_copy[y])
	{
		x = 0;
		while (data->map_copy[y][x])
		{
			if (data->map_copy[y][x] == 'P')
				data->pfand_amount++;
			x++;
		}
		y++;
	}
	printf("Availiable pfand: %d\n", data->pfand_amount);
}

void	collect_pfand(t_env *env)
{
	int	x;
	int	y;

	x = env->player->xc;
	y = env->player->yc;
	if (env->data->pfand_amount > 0
		&& is_pfand_around(x, y, env->data->map_copy, env->player))
	{
		env->data->map_copy[env->player->p_y][env->player->p_x] = '0';
		env->data->pfand_collected++;
	}
	if (env->data->pfand_amount == env->data->pfand_collected
		|| env->data->pfand_amount <= 0)
	{
		printf("All pfand is collected!\n");
		return ;
	}
	else if (env->data->pfand_amount > 0)
	{
		printf("pfand available: %d\n",
			env->data->pfand_amount - env->data->pfand_collected);
		printf("pfand collected: %d\n", env->data->pfand_collected);
	}
}

void	give_pfand_to_automat(t_env *env)
{
	if (env->data->looking_at == 'A'
		&& env->data->pfand_collected > 0)
	{
		env->player->pfand_sum += round(env->data->pfand_collected
				* 0.08 * 100) / 100;
		env->data->pfand_amount -= env->data->pfand_collected;
		env->data->pfand_collected = 0;
	}
	env->player->display_bon = !env->player->display_bon;
}

void	display_pfandbon(t_env *env)
{
	char	pfand_str[32];

	snprintf(pfand_str, sizeof(pfand_str),
		"%.2f EURO", env->player->pfand_sum);
	printf("Pfandbon: %s\n", pfand_str);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->pfandbon->img, 0, 0);
	mlx_set_font(env->mlx, env->mlx_win,
		"-misc-fixed-bold-r-normal--40-0-100-100-c-0-iso10646-1");
	mlx_string_put(env->mlx, env->mlx_win,
		WIDTH / 2 - 100, HEIGHT / 2, 0x000000, pfand_str);
}

int	is_pfand_around(int x, int y, char **map, t_player *player)
{
	player->p_x = x;
	player->p_y = y;
	if (map[y][x] && map[y][x] == 'P')
		return (1);
	if (map[y + 1][x] && map[y + 1][x] == 'P')
		player->p_y = y + 1;
	else if (map[y - 1][x] && map[y - 1][x] == 'P')
		player->p_y = y - 1;
	else if (map[y][x + 1] && map[y][x + 1] == 'P')
		player->p_x = x + 1;
	else if (map[y][x - 1] && map[y][x - 1] == 'P')
		player->p_x = x - 1;
	else
		return (0);
	return (1);
}
