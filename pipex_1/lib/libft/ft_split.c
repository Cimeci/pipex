/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:01:36 by inowak--          #+#    #+#             */
/*   Updated: 2024/10/09 18:01:28 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static void	*ft_free(char **tab, size_t i)
{
	while (i-- > 0)
		free(tab[i]);
	free(tab);
	return (0);
}

static char	*ft_strdup_pimp(const char *s, char c)
{
	char	*tab;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while ((s[len] != c) && s[len])
		len++;
	tab = malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	while (i < len)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

static char	**ft_splitv2(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			tab[j] = ft_strdup_pimp(&s[i], c);
			if (!tab[j])
				return (ft_free(tab, j));
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!tab)
		return (NULL);
	tab = ft_splitv2(s, c, tab);
	return (tab);
}
