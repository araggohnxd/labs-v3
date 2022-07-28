/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 23:13:14 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/03 01:02:41 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const size_t	src_len = ft_strlen(src);
	const size_t	dst_len = ft_strnlen(dst, size);

	if (dst_len == size)
		return (size + src_len);
	if (src_len < (size - dst_len))
		ft_memcpy((dst + dst_len), src, (src_len + 1));
	else
	{
		ft_memcpy((dst + dst_len), src, (size - dst_len - 1));
		dst[size - 1] = '\0';
	}
	return (dst_len + src_len);
}
