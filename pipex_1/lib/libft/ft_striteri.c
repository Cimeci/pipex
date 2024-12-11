/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:42:37 by inowak--          #+#    #+#             */
/*   Updated: 2024/10/10 17:43:02 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}

#include <stdio.h>

// Fonction callback pour appliquer une modification aux caractères de la chaîne
void    my_callback(unsigned int i, char *c)
{
    if (i % 2 == 0)
        *c = *c - 32; // Transforme les lettres en majuscule à chaque index pair (si c'est une lettre minuscule)
}

int main(void)
{
    char str[] = "hello world!";
    printf("Avant ft_striteri: %s\n", str);

    ft_striteri(str, my_callback);

    printf("Après ft_striteri: %s\n", str);
    return 0;
}

