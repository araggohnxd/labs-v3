/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:29:36 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/30 01:46:21 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fill an array allocated with malloc() with the given
 * number received at ft_utoa().
 * @param num Number to fill the array with.
 * @param arr Pointer to the array to fill.
 * @param size Size of the number used to fill the array.
 * @return Nothing.
**/
static void	ft_fill_array(t_uint num, char *arr, size_t size)
{
	if (num >= 10)
		ft_fill_array(num / 10, arr, size - 1);
	arr[size] = (num % 10) + '0';
}

char	*ft_utoa(t_uint n)
{
	char		*arr;
	t_uint		num;
	size_t		uint_size;

	num = n;
	uint_size = 1;
	while (n >= 10)
	{
		n /= 10;
		uint_size++;
	}
	arr = (char *) ft_calloc((uint_size + 1), sizeof(char));
	if (!arr)
		return (NULL);
	ft_fill_array(num, arr, (uint_size - 1));
	return (arr);
}
