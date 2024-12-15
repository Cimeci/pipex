/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 03:31:33 by marvin            #+#    #+#             */
/*   Updated: 2024/12/15 03:31:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *get_command(const char *cmd)
{
    const char *last_slash;
    size_t i;
    int in_quotes;

    last_slash = NULL;
    i = 0;
    in_quotes = 0;
    while (cmd[i] != '\0')
    {
        if (cmd[i] == '"' || cmd[i] == 39)
            in_quotes = !in_quotes;
        else if (cmd[i] == '/' && !in_quotes)
            last_slash = cmd + i;
        i++;
    }
    if (last_slash != NULL)
        return strdup(last_slash + 1);
    return strdup(cmd);
}

int main(int argc, char **argv)
{
    if (argc != 4)
        return (0);

    char *result1 = get_command(argv[1]);
    char *result2 = get_command(argv[2]);
    char *result3 = get_command(argv[3]);

    printf("Résultat pour path1 : %s\n", result1);
    printf("Résultat pour path2 : %s\n", result2);
    printf("Résultat pour cmd : %s\n", result3);

    free(result1);
    free(result2);
    free(result3);

    return 0;
}
