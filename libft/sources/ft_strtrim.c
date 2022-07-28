/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:44:48 by maolivei          #+#    #+#             */
/*   Updated: 2022/07/24 20:18:59 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;

	if (s1 && !set)
		return (ft_strdup(s1));
	if (!s1)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	s1_len = ft_strlen(s1);
	while (s1_len && ft_strchr(set, s1[s1_len]))
		s1_len--;
	return (ft_substr(s1, 0, (s1_len + 1)));
}
