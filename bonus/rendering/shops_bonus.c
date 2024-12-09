/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 01:16:15 by tlaukat           #+#    #+#             */
/*   Updated: 2024/12/09 01:16:15 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub_bonus.h"

int	filter_events(int keycode, t_env *env)
{
	if (keycode == SPACE || keycode == HK)
		return (toggle_pictures(keycode, env), 1);
	if (keycode == BK && SHOP_BEER == 0)
		return (toggle_pictures(keycode, env), 1);
	if (keycode == MK && SHOP_BREZEL == 0)
		return (toggle_pictures(keycode, env), 1);
	if (keycode == BK && env->player->player_pos == BEER)
		return (toggle_pictures(keycode, env), 1);
	if (keycode == MK && env->player->player_pos == BREZEL)
		return (toggle_pictures(keycode, env), 1);
	return (0);
}

void	handle_shop_events(int keycode, t_env *env)
{
	if (filter_events(keycode, env) == 1)
	{
		if (env->player->player_pos == BREZEL && BREZEL_WIN == 1)
			win(env);
		return ;
	}
	if (keycode != EK)
		return ;
	if (SHOP_BEER == 1 && env->data->looking_at == 'B')
		toggle_pictures(BK, env);
	if (SHOP_BREZEL == 1 && env->data->looking_at == 'M')
		toggle_pictures(MK, env);
	if (env->player->player_pos == BREZEL && BREZEL_WIN == 1)
		win(env);
}
