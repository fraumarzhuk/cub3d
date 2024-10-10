/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:24:53 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/10 16:35:16 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void init_mlx(t_env *env)
{
	env->mlx = mlx_init();
	env->mlx_win = mlx_new_window(env->mlx, 1000, 1000, "Cub 3D");
	mlx_loop(env->mlx);
	//add keys for exit
}