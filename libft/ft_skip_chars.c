/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 00:54:35 by maolivei          #+#    #+#             */
/*   Updated: 2022/07/20 00:54:59 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_skip_chars(char *str, int (*f)(int))
{
	size_t	index;

	index = 0;
	while (f(str[index]))
		++index;
	ft_strlcpy(str, (str + index), (ft_strlen(str) - index + 1));
}
