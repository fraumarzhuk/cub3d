/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:36:20 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/10 16:36:47 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int	key_press(int keycode, t_env *env)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(env->mlx, env->mlx_win);
		ft_destructor();
		exit(1);
	}
	return (0);
}