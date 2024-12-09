/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:36:20 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/26 15:15:23 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

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
	}
}

int	key_press(int keycode, t_env *env)
{
	if (keycode == ESC)
		destroy(env);
	if (keycode == WK)
		env->player->key_up = true;
	if (keycode == SK)
		env->player->key_down = true;
	if (keycode == AK)
		env->player->key_left = true;
	if (keycode == DK)
		env->player->key_right = true;
	if (keycode == LEFT)
		env->player->left_rotate = true;
	if (keycode == RIGHT)
		env->player->right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_env *env)
{
	if (keycode == ESC)
		destroy(env);
	if (keycode == WK)
		env->player->key_up = false;
	if (keycode == SK)
		env->player->key_down = false;
	if (keycode == AK)
		env->player->key_left = false;
	if (keycode == DK)
		env->player->key_right = false;
	if (keycode == LEFT)
		env->player->left_rotate = false;
	if (keycode == RIGHT)
		env->player->right_rotate = false;
	return (0);
}

int	destroy(t_env *env)
{
	ft_free_images(env);
	if (env->mlx_win)
		mlx_destroy_window(env->mlx, env->mlx_win);
	if (env->mlx)
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
	}
	ft_destructor();
	exit(0);
}
