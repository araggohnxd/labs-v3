/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 18:12:06 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/03 17:48:45 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	length;

	length = ft_strlen(s);
	while (length)
		if (*(s + length--) == (unsigned char) c)
			return ((char *)(s + (length + 1)));
	if (*(s + length--) == (unsigned char) c)
		return ((char *)(s + (length + 1)));
	return (NULL);
}
