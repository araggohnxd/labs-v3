/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 02:04:07 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/30 02:05:01 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_handler_integer(int number)
{
	size_t	num_size;
	char	*i_to_a;

	i_to_a = ft_itoa(number);
	ft_putstr_fd(i_to_a, STDOUT);
	num_size = ft_strlen(i_to_a);
	free(i_to_a);
	return (num_size);
}

int	ft_handler_unsigned(t_uint number)
{
	size_t	num_size;
	char	*u_to_a;

	u_to_a = ft_utoa(number);
	ft_putstr_fd(u_to_a, STDOUT);
	num_size = ft_strlen(u_to_a);
	free(u_to_a);
	return (num_size);
}

int	ft_handler_string(char *string)
{
	if (!string)
		return (ft_handler_string("(null)"));
	ft_putstr_fd(string, STDOUT);
	return (ft_strlen(string));
}

int	ft_handler_pointer(void *pointer)
{
	t_ulong	pointer_address;
	size_t	num_size;
	char	*arr;

	if (!pointer)
		return (ft_handler_string("(nil)"));
	pointer_address = (t_ulong) pointer;
	arr = ft_itoa_base(pointer_address, HEX_BASE_LOWER);
	ft_putstr_fd("0x", STDOUT);
	ft_putstr_fd(arr, STDOUT);
	num_size = (ft_strlen(arr));
	free(arr);
	return (num_size + 2);
}

int	ft_handler_hex(char specifier, t_uint number)
{
	size_t	num_size;
	char	*arr;

	if (specifier == HEXL)
		arr = ft_itoa_base(number, HEX_BASE_LOWER);
	else if (specifier == HEXU)
		arr = ft_itoa_base(number, HEX_BASE_UPPER);
	ft_putstr_fd(arr, STDOUT);
	num_size = ft_strlen(arr);
	free(arr);
	return (num_size);
}
