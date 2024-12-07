/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:31:11 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/26 15:21:47 by tlaukat          ###   ########.fr       */
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
	if (keycode == BK)
	{
		if (env->player->player_pos == BEER)
			env->player->player_pos = HANDS;
		else
			env->player->player_pos = BEER;
	}
	if (keycode == MK)
	{
		if (env->player->player_pos == BREZEL)
			env->player->player_pos = HANDS;
		else
			env->player->player_pos = BREZEL;
	}
	if (keycode == HK)
	{
		if (env->player->player_pos == HIDEPLAYER)
			env->player->player_pos = HANDS;
		else
			env->player->player_pos = HIDEPLAYER;
	}
	if (keycode == SPACE)
		env->player->display_rules = !env->player->display_rules;
	if (keycode == PK)
		collect_pfand(env);
	if (keycode == XK)
	{
		give_pfand_to_automat(env);
		env->player->display_bon = true;
	}
	env->player->render_move = true;
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
	if (keycode == XK)
		env->player->display_bon = false;
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
	int			dx;

	dx = x - WIDTH / 2;
	if (!y)
		write(0, "y\n", 0);
	if (env->player->mouse_on)
	{
		env->player->angle += dx * MOUSE_SENS;
		if (env->player->angle > 360)
			env->player->angle -= 360;
		if (env->player->angle < 0)
			env->player->angle += 360;
		env->player->right_rotate = true;
		env->player->left_rotate = true;
		mlx_mouse_move(env->mlx, env->mlx_win, WIDTH / 2, HEIGHT / 2);
	}
}
int	mouse_hook(int button, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		env->player->mouse_on = !env->player->mouse_on;
		if (env->player->mouse_on)
		{
			grab_mouse(env->mlx, env->mlx_win);
			mlx_mouse_hide(env->mlx, env->mlx_win);
			mlx_mouse_move(env->mlx, env->mlx_win, WIDTH / 2, HEIGHT / 2);
		}
		else
		{
			env->player->right_rotate = false;
			env->player->left_rotate = false;
			ungrab_mouse(env->mlx);
			mlx_mouse_show(env->mlx, env->mlx_win);
		}
	}
	return (0);
}

int	mouse_move_hook(int x, int y, t_env *env)
{
	if (env->player->mouse_on)
		rotate_with_mouse(env, x, y);
	return (0);
}
