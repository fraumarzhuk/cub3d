/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:13:08 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/14 11:53:56 by mzhukova         ###   ########.fr       */
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
		return (printf("No map is provided\n"));
	file_validation(argv[1], env);
	init_mlx(env);
	ft_destructor();
	return (0);
}
