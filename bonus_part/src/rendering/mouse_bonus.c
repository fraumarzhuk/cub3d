/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:57:40 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/09 17:23:33 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub_bonus.h"

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
