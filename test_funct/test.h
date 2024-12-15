/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:38:33 by marvin            #+#    #+#             */
/*   Updated: 2024/12/12 23:38:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_count_word(const char *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_free(char **tab);

#endif