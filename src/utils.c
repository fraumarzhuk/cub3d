/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:06:32 by mzhukova          #+#    #+#             */
/*   Updated: 2024/09/26 18:43:37 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void error_and_exit(char *str)
{
	printf("%s\n", str);
	ft_destructor();
	exit(1);
}

void init_env(t_env *env)
{
	env->data = (t_data *)ft_malloc(sizeof(t_data));
	env->img = (t_img *)ft_malloc(sizeof(t_img));
	env->player = (t_player *)ft_malloc(sizeof(t_player));
}