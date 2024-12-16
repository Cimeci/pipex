/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:52:12 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/16 13:52:12 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

char **ft_split(char const *s, char c);

void handle_child(int i, int n_cmds, int pipes[][2], int infile_fd, int outfile_fd, char **cmd, char **envp) {
    if (i == 0)
        dup2(infile_fd, STDIN_FILENO);
    else
        dup2(pipes[i - 1][0], STDIN_FILENO);

    if (i == n_cmds - 1)
        dup2(outfile_fd, STDOUT_FILENO);
    else
        dup2(pipes[i][1], STDOUT_FILENO);

    // Fermer tous les pipes dans les processus enfants
    for (int j = 0; j < n_cmds - 1; j++) {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }

    execve(cmd[0], cmd, envp);
    perror("execve failed");
    exit(EXIT_FAILURE);
}

void multi_pipe(int n_cmds, char **cmds[], char **envp, int infile_fd, int outfile_fd) {
    int pipes[n_cmds - 1][2];
    pid_t pids[n_cmds];

    for (int i = 0; i < n_cmds - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Pipe error");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < n_cmds; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            handle_child(i, n_cmds, pipes, infile_fd, outfile_fd, cmds[i], envp);
        }
    }

    // Parent: fermer tous les pipes
    for (int i = 0; i < n_cmds - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Attendre tous les enfants
    for (int i = 0; i < n_cmds; i++) {
        waitpid(pids[i], NULL, 0);
    }
}

int main(int argc, char **argv, char **envp) {
    if (argc != 6)
	{
        printf("Usage: ./a.out infile cmd1 cmd2 cmdn outfile\n");
        return EXIT_FAILURE;
    }

    int infile_fd = open(argv[1], O_RDONLY);
    int outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (infile_fd < 0 || outfile_fd < 0)
	{
        perror("File open error");
        return EXIT_FAILURE;
    }

    char **cmd1 = ft_split(argv[2], ' ');
    char **cmd2 = ft_split(argv[3], ' ');
    char **cmd3 = ft_split(argv[4], ' ');

    char **cmds[] = {cmd1, cmd2, cmd3};

    multi_pipe(3, cmds, envp, infile_fd, outfile_fd);

    close(infile_fd);
    close(outfile_fd);

    return 0;
}
