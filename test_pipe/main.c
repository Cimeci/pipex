/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 07:52:50 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/17 07:53:40 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main() {
    int fd[2]; // Tableau pour stocker les descripteurs
    char buffer[20];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // Écrire dans le pipe
    write(fd[1], "Hello, Pipe!", 12);

    // Lire depuis le pipe
    read(fd[0], buffer, 12);
    buffer[12] = '\0';
    printf("Message lu : %s\n", buffer);

    return 0;
}
