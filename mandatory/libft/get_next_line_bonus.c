/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:04:02 by mzhukova          #+#    #+#             */
/*   Updated: 2024/09/25 10:09:32 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_start(const char *remainder)
{
	int		len;
	char	*start;
	char	*temp;

	len = 0;
	while (remainder[len] != '\n' && remainder[len] != '\0')
		len++;
	start = ft_malloc(len + 2);
	if (!start)
		return (NULL);
	temp = start;
	while (*remainder != '\n' && *remainder != '\0')
	{
		*temp = *remainder;
		temp++;
		remainder++;
	}
	if (*remainder == '\n')
		*temp++ = '\n';
	*temp = '\0';
	return (start);
}

char	*get_remainder(const char *remainder)
{
	char	*end;
	char	*temp;
	int		n;

	n = 0;
	while (remainder[n] != '\n' && remainder[n] != '\0')
		n++;
	if (remainder[n] == '\0' || remainder[n + 1] == '\0' )
		return (NULL);
	end = ft_malloc(ftt_strlen(remainder) - n + 1);
	if (!end)
		return (NULL);
	temp = end;
	remainder += n + 1;
	while (*remainder != '\0')
		*temp++ = *remainder++;
	*temp = '\0';
	return (end);
}

char	*read_and_store(char *buffer, char **remainder)
{
	char	*res;
	char	*temp;
	char	*new_remainder;

	res = NULL;
	if (*remainder == NULL)
		*remainder = ftt_strdup(buffer);
	else
	{
		temp = ftt_strjoin(*remainder, buffer);
		ft_free(*remainder);
		*remainder = temp;
	}
	if (!*remainder)
		return (NULL);
	if (ftt_strrchr(*remainder, '\n') == NULL)
		return (NULL);
	else
	{
		res = get_start(*remainder);
		new_remainder = get_remainder(*remainder);
		ft_free(*remainder);
		*remainder = new_remainder;
		return (res);
	}
}

char	*process_remainder(char **remainder)
{
	char	*res;

	res = NULL;
	if (*remainder != NULL && **remainder != '\0')
	{
		if (ftt_strrchr(*remainder, '\n') != NULL)
		{
			res = read_and_store("", remainder);
		}
		else
		{
			res = ftt_strdup(*remainder);
			ft_free(*remainder);
			*remainder = NULL;
		}
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*remainder[MAX_FD];
	char		buffer[BUFFER_SIZE + 1];
	char		*res;
	size_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (ft_free(remainder[fd]), remainder[fd] = NULL, NULL);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		res = read_and_store(buffer, &remainder[fd]);
		if (res != NULL)
			return (res);
	}
	return (process_remainder(&remainder[fd]));
}
