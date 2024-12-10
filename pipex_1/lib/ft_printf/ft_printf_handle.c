/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:41:37 by marvin            #+#    #+#             */
/*   Updated: 2024/10/20 20:41:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_int(va_list ap)
{
	int	d;
	int	count;

	count = 0;
	d = va_arg(ap, int);
	count += ft_putnbr_base(d, "0123456789");
	return (count);
}

int	ft_handle_unsigned(va_list ap)
{
	unsigned int	u;
	int				count;

	count = 0;
	u = va_arg(ap, unsigned int);
	count += ft_putnbr_base(u, "0123456789");
	return (count);
}

int	ft_handle_hex(va_list ap, char fmt)
{
	unsigned int	x;
	int				count;

	count = 0;
	x = va_arg(ap, unsigned int);
	if (fmt == 'x')
		count += ft_putnbr_base(x, "0123456789abcdef");
	else
		count += ft_putnbr_base(x, "0123456789ABCDEF");
	return (count);
}

int	ft_handle_pointer(va_list ap)
{
	void	*p;
	int		count;

	count = 0;
	p = va_arg(ap, void *);
	if (p == NULL)
		count += ft_putstr("(nil)");
	else
		count += ft_p(p);
	return (count);
}

int	ft_handle_string(va_list ap)
{
	char	*s;
	int		count;

	count = 0;
	s = va_arg(ap, char *);
	if (s)
		count += ft_putstr(s);
	else
		count += ft_putstr("(null)");
	return (count);
}
