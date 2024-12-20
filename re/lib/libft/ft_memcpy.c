/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:01:36 by inowak--          #+#    #+#             */
/*   Updated: 2024/10/09 18:01:28 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned const char	*dtr;	
	unsigned char		*ptr;
	int					i;

	if (!dest && !src)
		return (0);
	i = 0;
	dtr = src;
	ptr = dest;
	while (n)
	{
		ptr[i] = dtr[i];
		i++;
		n--;
	}
	return (dest);
}
