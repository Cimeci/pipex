/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:50:00 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/17 18:51:06 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipex
{
    int     *pipe_fd;
    int     infile;
    int     outfile;
    int     cmd_count;
    pid_t   *pids;
}           t_pipex;

void    free_split(char **split);
void    error_exit(const char *msg, t_pipex *pipex);
char    *get_env_path(const char *name, char **env);
char    *find_path(char *cmd, char **env);
void    execute_command(char *cmd, char **env);
void    setup_pipes(t_pipex *pipex);
void    close_pipes(t_pipex *pipex);
void    child_process(t_pipex *pipex, char **argv, char **env, int i);