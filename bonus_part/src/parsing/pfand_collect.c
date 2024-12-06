/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfand_collect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaeggi <chaeggi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:31:01 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/06 17:57:54 by chaeggi          ###   ########.fr       */
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
	if (env->data->pfand_amount > 0 && is_char_around(x, y, env->data->map_copy, 'P'))
	{
		env->data->map_copy[y][x] = '0';
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
	int		x, y;
	// char	pfand_str[32];

	x = env->player->xc;
	y = env->player->yc;
	if (is_char_around(x, y, env->data->map_copy, 'A'))
	{
		env->player->pfand_sum = round(env->data->pfand_collected * 0.08 * 100) / 100;
		env->data->pfand_amount -= env->data->pfand_collected;
		// snprintf(pfand_str, sizeof(pfand_str), "%.2f EURO", env->player->pfand_sum);
		// printf("Pfandbon: %s\n", pfand_str);
		// mlx_put_image_to_window(env->mlx, env->mlx_win, env->pfandbon->img, 0, 0);
		// mlx_set_font(env->mlx, env->mlx_win, "-adobe-helvetica-bold-i-normal--40-0-0-0-p-0-iso8859-15");
		// mlx_string_put(env->mlx, env->mlx_win, WIDTH / 2 - 100, HEIGHT / 2, 0x000000, pfand_str);
		env->data->pfand_collected = 0;
		//env->player->display_bon = true;
	}
}

int	is_char_around(int x, int y, char **map, char c)
{
	if (map[y + 1][x] && map[y + 1][x] == c)
		return (1);
	if (map[y - 1][x] && map[y - 1][x] == c)
		return (1);
	if (map[y][x + 1] && map[y][x + 1] == c)
		return (1);
	if (map[y][x - 1] && map[y][x - 1] == c)
		return (1);
	else
		return (0);
}
