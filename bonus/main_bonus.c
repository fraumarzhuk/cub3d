/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:13:08 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/09 17:23:58 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

int	main(int argc, char **argv)
{
	t_env	*env;

	ft_alloc_init();
	env = (t_env *)ft_malloc(sizeof(t_env));
	init_env(env);
	if (argc != 2)
		error_and_exit("Incorrect amount of arguments\n");
	file_validation(argv[1], env);
	init_mlx(env);
	ft_destructor();
	return (0);
}
