/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:11:15 by maolivei          #+#    #+#             */
/*   Updated: 2022/04/08 16:32:24 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*aux_node;

	aux_node = *lst;
	while (aux_node)
	{
		aux_node = aux_node->next;
		ft_lstdelone(*lst, del);
		*lst = aux_node;
	}
	*lst = NULL;
}
