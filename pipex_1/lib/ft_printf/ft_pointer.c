/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:30:38 by inowak--          #+#    #+#             */
/*   Updated: 2024/11/20 10:30:34 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_pointer(uintptr_t nbr, const char *base)
{
	int	base_len;
	int	count;

	base_len = 16;
	count = 0;
	if (nbr >= (uintptr_t)base_len)
		count += ft_putnbr_pointer(nbr / base_len, base);
	ft_putchar(base[nbr % base_len]);
	count++;
	return (count);
}

int	ft_p(void *ptr)
{
	uintptr_t	address;
	int			count;

	count = 0;
	address = (uintptr_t)ptr;
	ft_putstr("0x");
	count += ft_putnbr_pointer(address, "0123456789abcdef");
	return (2 + count);
}
