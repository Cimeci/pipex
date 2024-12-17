/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:35:16 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/17 09:23:00 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_after_line(char *s, int c)
{
	char	*tmp;
	int		i;
	int		j;
	char	*after_line;

	j = 1;
	i = 0;
	tmp = ft_strchr(s, c);
	if (!tmp)
	{
		free(s);
		return (NULL);
	}
	after_line = malloc(sizeof(char) * (ft_strlen(tmp + 1) + 1));
	if (!after_line)
		return (NULL);
	while (tmp[j])
		after_line[i++] = tmp[j++];
	after_line[i] = '\0';
	free(s);
	return (after_line);
}

char	*ft_line(char *s, int c)
{
	char	*tab;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (s[size] != c && s[size])
		size++;
	if (s[size] == c)
		size++;
	tab = malloc(sizeof(char) * size + 1);
	if (!tab)
		return (NULL);
	while (s[i] != c && s[i])
	{
		tab[i] = s[i];
		i++;
	}
	if (s[i] == c)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*new_str;
	size_t	j;

	new_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	j = 0;
	while (s1 && s1[j])
	{
		new_str[j] = s1[j];
		j++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		new_str[ft_strlen(s1) + j] = s2[j];
		j++;
	}
	new_str[ft_strlen(s1) + j] = '\0';
	free(s1);
	return (new_str);
}
