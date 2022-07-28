/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:39:59 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/05 14:57:35 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*csrc = (char *) src;
	char		*cdst;

	cdst = (char *) dest;
	if (dest > src)
		while (n--)
			*(cdst + n) = *(csrc + n);
	else if (dest < src)
		while (n--)
			*cdst++ = *csrc++;
	return (dest);
}
