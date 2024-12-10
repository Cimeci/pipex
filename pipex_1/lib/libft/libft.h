/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:34:31 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/10 14:40:50 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

size_t	ft_count_word(const char *s, char c);
char	**ft_split(char const *s, char c);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);

#endif