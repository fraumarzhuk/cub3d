/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:51:04 by mzhukova          #+#    #+#             */
/*   Updated: 2024/05/04 17:04:44 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;

	p = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (p == NULL)
		return (NULL);
	ft_strlcpy(p, s1, (ft_strlen(s1) + 1));
	return (p);
}

// int main()
// {
//     const char *str = "bonjour";
//     char *duplicate = ft_strdup(str);
//     if (duplicate != NULL)
//     {
//         printf("Original string: %s\n", str);
//         printf("Duplicated string: %s\n", duplicate);
//         free(duplicate); 
//     }
//     return (0);
// }