/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfand_collect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:31:01 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/06 11:28:56 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

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
	if (env->data->map_copy[y][x] == 'P')
	{
		env->data->map_copy[y][x] = '0';
		env->data->pfand_collected++;
	}
	if (env->data->pfand_amount == env->data->pfand_collected
		|| env->data->pfand_amount <= 0)
		printf("All pfand is collected!\n");
	else
	{
		printf("pfand available: %d\n",
			env->data->pfand_amount - env->data->pfand_collected);
		printf("pfand collected: %d\n", env->data->pfand_collected);
	}
}

void	give_pfand_to_automat(t_env *env)
{
	int		x;
	int		y;

	x = env->player->xc;
	y = env->player->yc;
	if (is_automat_around(x, y, env->data->map_copy))
	{
		//cut the numbers after 8
		env->player->pfand_sum = env->data->pfand_collected * 0.08;
		env->data->pfand_amount -= env->data->pfand_collected;
		printf("Pfandbon: %f€\n", env->player->pfand_sum);
		mlx_put_image_to_window(env->mlx, env->mlx_win, env->pfandbon->img, 100, 100);
		mlx_string_put(env->mlx, env->mlx_win, 140, 140, BLOCK_COL, ft_itoa(env->player->pfand_sum));
		env->data->pfand_collected = 0;
		env->player->display_bon = true;
	}
}

int	is_automat_around(int x, int y, char **map)
{
	if (map[y + 1][x] && map[y + 1][x] == 'A')
		return (1);
	if (map[y - 1][x] && map[y - 1][x] == 'A')
		return (1);
	if (map[y][x + 1] && map[y][x + 1] == 'A')
		return (1);
	if (map[y][x - 1] && map[y][x - 1] == 'A')
		return (1);
	else
		return (0);
}
