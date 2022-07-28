/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:55:56 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/03 01:02:37 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const size_t	src_len = ft_strlen(src);

	if ((src_len + 1) < size)
		ft_memcpy(dst, src, (src_len + 1));
	else if (size != 0)
	{
		ft_memcpy(dst, src, (size - 1));
		dst[size - 1] = '\0';
	}
	return (src_len);
}
