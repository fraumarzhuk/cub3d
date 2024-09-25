/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:39:07 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/09/25 10:09:40 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ftt_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!*s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ftt_strrchr(const char *s, int c)
{
	int	i;

	i = ftt_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

char	*ftt_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_malloc((ftt_strlen(s1) + ftt_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (*s1)
	{
		result[i++] = *s1;
		s1++;
	}
	while (*s2)
	{
		result[i++] = *s2;
		s2++;
	}
	result[i++] = '\0';
	return (result);
}

void	*ftt_calloc(int count, int size)
{
	char	*p;
	int		i;

	p = ft_malloc(count * size);
	if (!p)
		return (NULL);
	i = 0;
	while (i < count * size)
		p[i++] = 0;
	return (p);
}

char	*ftt_strdup(const char *s)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = ft_malloc ((sizeof(char)) * (ftt_strlen(s) + 1));
	if (!s2 || !s)
		return (NULL);
	while (s[i] != '\0')
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
