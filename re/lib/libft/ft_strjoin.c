/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:43:22 by inowak--          #+#    #+#             */
/*   Updated: 2024/10/24 13:07:11 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	tab = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tab)
		return (NULL);
	if (s1)
	{
		while (i < ft_strlen(s1))
			tab[j++] = s1[i++];
	}
	i = 0;
	while (i < ft_strlen(s2))
		tab[j++] = s2[i++];
	tab[j] = '\0';
	return (tab);
}
