/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:47:06 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/09/30 12:27:01 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i])
	{
		ft_free(split[i]);
		i++;
	}
	ft_free(split);
}

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (((str[i] < 48) || (str[i] > 57)))
			return (0);
		i++;
	}
	return (1);
}

void	*my_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf("Malloc failed. You used all of your memory bruh\n");
		return (NULL);
	}
	return (ptr);
}

char	*trim_spaces(char *str)
{
	char *res;
	res = str;
	
	while (*res && is_space(*res))
		res++;
	return (res);
}

int is_space(char c)
{
	return (c == ' ' || c == '\v' || c == '\f' || c == '\r');
}