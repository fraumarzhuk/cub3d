/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:36:20 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/28 12:26:22 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int	key_press(int keycode, t_env *env)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(env->mlx, env->mlx_win);
		ft_destructor();
		exit(0);
	}
	if (keycode == WK)
		env->player->key_up = true;
	if (keycode == SK)
		env->player->key_down = true;
	if (keycode == AK)
		env->player->key_left = true;
	if (keycode == DK)
		env->player->key_right = true;
	return (0);
}

int	key_release(int keycode, t_env *env)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(env->mlx, env->mlx_win);
		ft_destructor();
		exit(0);
	}
	if (keycode == WK)
		env->player->key_up = false;
	if (keycode == SK)
		env->player->key_down = false;
	if (keycode == AK)
		env->player->key_left = false;
	if (keycode == DK)
		env->player->key_right = false;
	return (0);
}

int	destroy(t_env *env)
{
	if (env->mlx_win)
		mlx_destroy_window(env->mlx, env->mlx_win);
	if (env->mlx)
		mlx_destroy_display(env->mlx);
	ft_destructor();
	exit(0);
}