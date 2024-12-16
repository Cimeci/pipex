/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:50:00 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/16 13:35:41 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/lib.h"
# include <fcntl.h>
# include <stdio.h>
#include <sys/wait.h>

typedef struct s_pipex
{
	int		pipe_fd[2];
	pid_t	pid[2];
}			t_pipex;

#endif