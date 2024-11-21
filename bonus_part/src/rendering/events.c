/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:36:20 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/21 18:56:54 by mzhukova         ###   ########.fr       */
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
	if (keycode == LEFT)
		env->player->left_rotate = true;
	if (keycode == RIGHT)
		env->player->right_rotate = true;
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
	if (keycode == LEFT)
		env->player->left_rotate = false;
	if (keycode == RIGHT)
		env->player->right_rotate = false;
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
void	rotate_with_mouse(t_env *env, int x, int y)
{
	int dx;
	int dy;

	dx = x - WIDTH / 2;
	dy = y - HEIGHT / 2;
	if (env->player->mouse_on)
	{
		env->player->angle += dx * MOUSE_SENS;
		if (env->player->angle > 360)
			env->player->angle -= 360;
		if (env->player->angle < 0)
			env->player->angle += 360;
		env->player->right_rotate = false;
		env->player->left_rotate = false;
	}
	//mlx_mouse_move(env->mlx, env->mlx_win, WIDTH / 2, HEIGHT / 2);
}
int	mouse_hook(int button, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (button == 1)
		env->player->mouse_on = true;
	else if (button == 0)
		env->player->mouse_on = false;
	return (0);
}

int	mouse_move_hook(int x, int y, t_env *env)
{
	if (env->player->mouse_on)
		rotate_with_mouse(env, x, y);
	return (0);
}