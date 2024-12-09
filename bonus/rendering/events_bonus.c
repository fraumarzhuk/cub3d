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

#include "../../inc/cub_bonus.h"

int	key_press(int keycode, t_env *env)
{
	if (keycode == ESC)
		destroy(env);
	if (keycode == EK || keycode == BK || keycode == MK || keycode == HK
		|| keycode == SPACE)
		handle_shop_events(keycode, env);
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
	if ((keycode == LEFT || keycode == RIGHT) && env->player->mouse_on)
		mouse_hook(1, 0, 0, env);
	if (keycode == PK)
		collect_pfand(env);
	if (keycode == XK)
		give_pfand_to_automat(env);
	env->player->render_move = true;
	return (0);
}

void	toggle_pictures(int keycode, t_env *env)
{
	if (keycode == SPACE)
		env->player->display_rules = !env->player->display_rules;
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
}

int	key_release(int keycode, t_env *env)
{
	if (keycode == ESC)
	{
		destroy(env);
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

void	win(t_env *env)
{
	printf("You win!\n");
	destroy(env);
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
