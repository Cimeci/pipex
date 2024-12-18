/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:50:00 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/18 11:32:45 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../lib/lib.h"

typedef struct s_pipex
{
	int		*pipe_fd;
	pid_t	pid[2];
}			t_pipex;

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**env;
}			t_data;

void	check_input(t_data *data);
char	*find_path(char **env, char *cmd);
// char	*my_getenv(const char *name, char **env);

// void	execute_command(char *cmd, char **env);
// void	handle_to_first_last(t_pipex *pipex, int idx, t_data data)
void	process_child(t_pipex *pipex, int idx, t_data data);

t_pipex	*init_pipex(int argc);
t_data	*ft_init_data(int argc, char **argv, char **env, t_pipex *pipex);

void	close_pipes(t_pipex *pipex, int pipe_count);
void	ft_puterror(int i);

#endif
