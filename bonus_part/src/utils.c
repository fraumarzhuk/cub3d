/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:06:32 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/12 17:56:18 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	error_and_exit(char *str)
{
	printf("%s\n", str);
	ft_destructor();
	exit(1);
}

void	copy_spaces(char *map_line, char *new_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map_line[i])
	{
		if (map_line[i] == '\t')
		{
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
		}
		else
			new_line[j++] = map_line[i];
		i++;
	}
	new_line[j++] = '\0';
}

void	ft_free_images(t_env *env)
{
	if (env->canvas->img)
		mlx_destroy_image(env->mlx, env->canvas->img);
	if (env->scene_canvas->img)
		mlx_destroy_image(env->mlx, env->scene_canvas->img);
	if (env->ceiling->img)
	{
		mlx_destroy_image(env->mlx, env->ceiling->img);
		mlx_destroy_image(env->mlx, env->floor->img);
		mlx_destroy_image(env->mlx, env->north_wall->img);
		mlx_destroy_image(env->mlx, env->south_wall->img);
		mlx_destroy_image(env->mlx, env->west_wall->img);
		mlx_destroy_image(env->mlx, env->east_wall->img);
		mlx_destroy_image(env->mlx, env->mini_map->img);
		mlx_destroy_image(env->mlx, env->enjoyer->img);
		mlx_destroy_image(env->mlx, env->enj_beer->img);
		mlx_destroy_image(env->mlx, env->enj_brezel->img);
		mlx_destroy_image(env->mlx, env->brezel_shop->img);
		mlx_destroy_image(env->mlx, env->beer_shop->img);
		mlx_destroy_image(env->mlx, env->pfand->img);
		mlx_destroy_image(env->mlx, env->pfandautomat->img);
		mlx_destroy_image(env->mlx, env->loading_screen->img);
		mlx_destroy_image(env->mlx, env->pfandbon->img);
		mlx_destroy_image(env->mlx, env->rules->img);
	}
}
