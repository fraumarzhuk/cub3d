/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:00:18 by mzhukova          #+#    #+#             */
/*   Updated: 2024/09/26 18:30:42 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alloc.h"

void	*ft_malloc(size_t size)
{
	t_allocs	*allocs;
	void		*ptr;

	allocs = ft_allocs(NULL);
	if (allocs == NULL)
		return (malloc(size));
	ptr = malloc(size);
	if (ptr == NULL)
	{
		printf("Memory allocation failed\n");
		ft_destructor();
		exit(EXIT_FAILURE);
	}
	add_allocnode(&allocs, create_alloc(ptr));
	return (ptr);
}

// static void	ft_bzero(void *s, size_t n)
// {
// 	unsigned char	*ptr;

// 	ptr = s;
// 	while (n-- > 0)
// 		*ptr++ = 0;
// }
