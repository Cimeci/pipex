/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:39:39 by marvin            #+#    #+#             */
/*   Updated: 2024/10/20 20:39:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_char(va_list ap)
{
	char	c;
	int		count;

	count = 0;
	c = (char) va_arg(ap, int);
	count += ft_putchar(c);
	return (count);
}

int	ft_handle_conversion(const char *fmt, va_list ap)
{
	int	size;

	size = 0;
	if (*fmt == 's')
		size += ft_handle_string(ap);
	else if (*fmt == 'c')
		size += ft_handle_char(ap);
	else if (*fmt == '%')
	{
		ft_putchar('%');
		size += 1;
	}
	else if (*fmt == 'd' || *fmt == 'i')
		size += ft_handle_int(ap);
	else if (*fmt == 'u')
		size += ft_handle_unsigned(ap);
	else if (*fmt == 'x' || *fmt == 'X')
		size += ft_handle_hex(ap, *fmt);
	else if (*fmt == 'p')
		size += ft_handle_pointer(ap);
	return (size);
}

int	ft_printf(const char *fmt, ...)
{
	int		total_size;
	va_list	ap;

	total_size = 0;
	va_start(ap, fmt);
	if (fmt == NULL)
		return (-1);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			total_size = total_size + ft_handle_conversion(fmt, ap);
		}
		else
		{
			ft_putchar(*fmt);
			total_size++;
		}
		fmt++;
	}
	va_end(ap);
	return (total_size);
}
