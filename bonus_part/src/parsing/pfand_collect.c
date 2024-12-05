/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfand_collect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:31:01 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/05 14:50:12 by mzhukova         ###   ########.fr       */
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
		printf("pfand available: %d\n", env->data->pfand_amount);
		printf("pfand collected: %d\n", env->data->pfand_collected);
	}
}

void	give_pfand_to_automat(t_env *env)
{
	double	sum;
	int		x;
	int		y;

	x = env->player->xc;
	y = env->player->yc;
	if (env->data->map_copy[y][x] == 'A')
	{
		sum = env->data->pfand_collected * 0.08;
		env->data->pfand_amount -= env->data->pfand_collected;
		printf("Pfandbon: %f€\n", sum);
		/* place the window with pfandbon on a screen here? */
		env->data->pfand_collected = 0;
	}
}
