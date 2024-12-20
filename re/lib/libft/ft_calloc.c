/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:20:53 by inowak--          #+#    #+#             */
/*   Updated: 2024/10/19 08:58:59 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	len;
	void	*tab;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > (size_t) - 1 / size)
		return (0);
	len = nmemb * size;
	tab = malloc(len);
	if (!tab)
		return (NULL);
	ft_bzero(tab, len);
	return (tab);
}
