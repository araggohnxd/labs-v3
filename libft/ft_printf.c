/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:39:10 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/30 01:59:01 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_handle_specifier(char specifier, va_list ap)
{
	if (specifier == INT || specifier == DEC)
		return (ft_handler_integer(va_arg(ap, int)));
	else if (specifier == UINT)
		return (ft_handler_unsigned(va_arg(ap, t_uint)));
	else if (specifier == STR)
		return (ft_handler_string(va_arg(ap, char *)));
	else if (specifier == PTR)
		return (ft_handler_pointer(va_arg(ap, void *)));
	else if (specifier == HEXL || specifier == HEXU)
		return (ft_handler_hex(specifier, va_arg(ap, t_uint)));
	else if (specifier == CHAR)
	{
		ft_putchar_fd((char) va_arg(ap, int), STDOUT);
		return (1);
	}
	else if (specifier == PERCENT)
	{
		ft_putchar_fd('%', STDOUT);
		return (1);
	}
	ft_putchar_fd('%', STDOUT);
	ft_putchar_fd(specifier, STDOUT);
	return (2);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		chars_written;

	va_start(ap, format);
	chars_written = 0;
	while (*format)
	{
		while (*format && *format != '%')
		{
			ft_putchar_fd(*format++, STDOUT);
			++chars_written;
		}
		if (*format == '%')
			chars_written += ft_handle_specifier(*++format, ap);
		if (!*format)
			break ;
		++format;
	}
	va_end(ap);
	return (chars_written);
}
