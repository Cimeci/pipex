/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:50:09 by marvin            #+#    #+#             */
/*   Updated: 2024/10/20 20:50:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_len_putnbr_base(long long nbr, const char *base)
{
	int	count;
	int	base_len;

	base_len = 0;
	count = 0;
	while (base[base_len])
		base_len++;
	if (nbr < 0)
	{
		count ++;
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		nbr = nbr / base_len;
		count ++;
	}
	return (count);
}

int	ft_putnbr_base(long long nbr, const char *base)
{
	unsigned long	base_length;
	int				count;

	count = 0;
	base_length = 0;
	while (base[base_length])
		base_length++;
	if (nbr == 0)
		count++;
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = -nbr;
		count++;
	}
	if (nbr >= (long long)base_length)
		ft_putnbr_base(nbr / base_length, base);
	ft_putchar(base[nbr % base_length]);
	count += ft_len_putnbr_base(nbr, base);
	return (count);
}

int	ft_putstr(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}
