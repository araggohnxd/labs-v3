/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_null.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:18:13 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/01 19:52:45 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_null(char **s1, char **s2)
{
	char	*str;

	str = ft_strjoin(*s1, *s2);
	ft_memfree((void *) s1);
	ft_memfree((void *) s2);
	return (str);
}
