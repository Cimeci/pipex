/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:43:54 by inowak--          #+#    #+#             */
/*   Updated: 2024/10/10 09:58:57 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_check(const char c, const char *set)
{
	size_t	i;

	i = 0;
	while (c != set[i] && set[i])
		i++;
	if (!set[i])
		return (0);
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;

	if (!s1 || !set)
		return (NULL);
	if (!*s1 || !*set)
		return (ft_strdup(s1));
	while (ft_check(*s1, set))
		s1++;
	size = ft_strlen(s1);
	while (size && ft_check(s1[size - 1], set))
		size--;
	return (ft_substr(s1, 0, size));
}
