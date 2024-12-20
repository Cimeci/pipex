/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:40:47 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/20 09:36:19 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_error(t_pipex *pipex, t_data *data)
{
	perror("Error");
	ft_free_all(pipex, data);
	exit(1);
}

void	ft_puterror(int i)
{
	if (i == 1)
		perror("Error");
	if (i == 0)
		ft_putendl_fd("ERROR", 2);
	if (i == 2)
	{
		ft_putstr_fd("Invalid format : ./pipex infile cmd1 ", 2);
		ft_putendl_fd("cmd2 ... cmdn outfile", 2);
	}
	if (i == 3)
	{
		ft_putstr_fd("Invalid format : ./pipex infile cmd1 ", 2);
		ft_putendl_fd("cmd2 outfile", 2);
	}
	exit(0);
}

void	close_pipes(t_pipex *pipex, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count * 2)
		close(pipex->pipe_fd[i++]);
}

void	ft_free_all(t_pipex *pipex, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->allocated_count)
	{
		if (data->allocated_cmds[i])
			free(data->allocated_cmds[i]);
		i++;
	}
	if (data->allocated_cmds)
		free(data->allocated_cmds);
	if (pipex->pipe_fd)
		free(pipex->pipe_fd);
	if (pipex)
		free(pipex);
	if (data)
		free(data);
}
