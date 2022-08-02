/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:52:03 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/01 19:57:11 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_extract_line(char *buffer, char *cache)
{
	size_t	i;
	char	*aux;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		++i;
	aux = ft_substr(buffer, 0, (i + 1));
	if (buffer[i] && buffer[i + 1])
		ft_strlcpy(cache, &buffer[i + 1], (ft_strlen(&buffer[i + 1]) + 1));
	else
		ft_bzero(cache, ft_strlen(cache));
	free(buffer);
	return (aux);
}

static char	*ft_read_line(int fd, char *buffer)
{
	int		read_ret;
	char	*aux;

	read_ret = TRUE;
	while (read_ret)
	{
		if (ft_strchr(buffer, '\n'))
			break ;
		aux = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!aux)
			return (NULL);
		read_ret = read(fd, aux, BUFFER_SIZE);
		if (read_ret < 1)
		{
			free(aux);
			break ;
		}
		aux[read_ret] = '\0';
		buffer = ft_strjoin_free_null(&buffer, &aux);
	}
	if (!*buffer)
		ft_memfree((void *) &buffer);
	return (buffer);
}

char	*ft_gnl(int fd)
{
	static char	cache[BUFFER_SIZE + 1];
	char		*buffer;

	if (fd < 0 || fd >= MAX_FD_VALUE || BUFFER_SIZE < 1)
		return (NULL);
	buffer = ft_read_line(fd, ft_strdup(cache));
	return (ft_extract_line(buffer, cache));
}
