/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:31:34 by maolivei          #+#    #+#             */
/*   Updated: 2022/07/29 15:32:53 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_free(char **s1, char const *set)
{
	char	*trim;

	trim = ft_strtrim(*s1, set);
	ft_memfree((void *) s1);
	return (trim);
}
