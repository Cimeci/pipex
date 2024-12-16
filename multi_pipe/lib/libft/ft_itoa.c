/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:18:25 by inowak--          #+#    #+#             */
/*   Updated: 2024/10/10 10:30:31 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*tab;
	int			i;
	long int	nb;

	nb = n;
	i = ft_count(nb);
	tab = malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (NULL);
	tab[i--] = '\0';
	if (nb == 0)
		tab[0] = '0';
	if (nb < 0)
	{
		tab[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		tab[i--] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (tab);
}
