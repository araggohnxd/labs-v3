/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 21:35:26 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/05 14:53:06 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*us1 = (unsigned char *) s1;
	const unsigned char	*us2 = (unsigned char *) s2;

	while (n--)
		if (*us1++ != *us2++)
			return (*(us1 - 1) - *(us2 - 1));
	return (0);
}
