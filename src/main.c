/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:13:08 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/09 16:54:13 by mzhukova         ###   ########.fr       */
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
		error_and_exit("Incorrect amount of arguments");
	file_validation(argv[1], env);
	init_mlx(env);
	destroy(env);
	return (0);
}
