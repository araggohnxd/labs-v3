/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 18:35:38 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/03 03:23:48 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n--)
		if (*(unsigned char *) s1++ != *(unsigned char *) s2++)
			return (*(unsigned char *)(s1 - 1) - *(unsigned char *)(s2 - 1));
	return (0);
}
