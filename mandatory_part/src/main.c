/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:13:08 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/25 23:32:42 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

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
	destroy(env);
	return (0);
}
