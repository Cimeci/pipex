/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:50:00 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/17 19:46:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
#include "../lib/lib.h"

typedef struct s_pipex
{
    int *pipe_fd;
    pid_t pid[2];
} t_pipex;

char    *find_path(char **env, char *cmd);
char    *my_getenv(const char *name, char **env);
void    execute_command(char *cmd, char **env);
t_pipex *init_pipex(int argc);
void    close_pipes(t_pipex *pipex, int pipe_count);
void    process_child(t_pipex *pipex, int idx, int argc, char **argv, char **env);

#endif
