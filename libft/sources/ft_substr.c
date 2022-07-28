/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:23:25 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/03 03:30:17 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	malloc_size;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start < s_len)
		malloc_size = s_len - start;
	if (start >= s_len)
		malloc_size = 0;
	if (malloc_size > len)
		malloc_size = len;
	substr = (char *) malloc(sizeof(char) * (malloc_size + 1));
	if (substr == NULL)
		return (NULL);
	if (malloc_size == 0)
	{
		substr[0] = '\0';
		return (substr);
	}
	ft_strlcpy(substr, (s + start), (malloc_size + 1));
	return (substr);
}
