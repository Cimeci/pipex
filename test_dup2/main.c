/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 07:58:16 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/17 08:25:08 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Rediriger stdout (descripteur 1) vers le fichier
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        return 1;
    }

    close(fd); // On peut fermer fd, car dup2 a fait une copie

    // Écrire sur stdout (sera écrit dans output.txt)
    printf("Ceci est écrit dans le fichier.\n");
    printf("Redirection réussie avec dup2 !\n");

    return 0;
}
