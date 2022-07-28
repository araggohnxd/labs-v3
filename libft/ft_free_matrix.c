/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 22:01:18 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/03 17:39:24 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(void ***matrix)
{
	void	**aux;

	aux = *matrix;
	while (*aux)
		ft_memfree((void *) aux++);
	ft_memfree((void *) matrix);
}
