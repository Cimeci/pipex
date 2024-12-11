/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:27 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/11 09:20:28 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        return (0);
    // Test de open, write, close
    int fd = open(argv[1], O_WRONLY | O_TRUNC);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    write(fd, "yo la team\n", 12);
    close(fd);

    // Test de fork, pipe, dup2, et execve
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        // Enfant : rediriger stdout vers le pipe
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execlp("ls", "ls", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent : lire depuis le pipe
        close(pipefd[1]);
        char buffer[128];
        int n = read(pipefd[0], buffer, sizeof(buffer) - 1);
        if (n > 0) {
            buffer[n] = '\0';
            printf("Output from child: %s\n", buffer);
        }
        close(pipefd[0]);
        wait(NULL);
    }

    // Test de access, unlink
    if (access(argv[1], F_OK) == 0) {
        printf("File exists\n");
        // unlink("test.txt");
    } else {
        perror("access");
    }

    return 0;
}
