/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:50:00 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/19 11:28:21 by inowak--         ###   ########.fr       */
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

//////////////////////////
//	 	 struct			//
//////////////////////////

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
	char	**allocated_cmds;
	int		allocated_count;
}			t_data;

//////////////////////////
//		ft_parsing.c	//
//////////////////////////

int		check_input(t_data *data);
char	*find_path(char **env, char *cmd);

//////////////////////////
//		ft_process.c	//
//////////////////////////

void	process_child(t_pipex *pipex, int idx, t_data data);

//////////////////////////
//		ft_init.c  		//
//////////////////////////

t_pipex	*init_pipex(int argc);
t_data	*ft_init_data(int argc, char **argv, char **env, t_pipex *pipex);

//////////////////////////
//		ft_clean.c	  	//
//////////////////////////

void	close_pipes(t_pipex *pipex, int pipe_count);
void	ft_puterror(int i);
void	ft_free_all(t_pipex *pipex, t_data *data);

#endif
