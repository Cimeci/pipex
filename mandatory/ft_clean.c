/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:40:47 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/21 14:06:21 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_error(t_pipex *pipex, t_data *data)
{
	perror("Error");
	ft_free_all(pipex, data);
	exit(1);
}

void	free_cmd_a_pn(char **cmd_a, char *pn)
{
	ft_free(cmd_a);
	free(pn);
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

// ft_putstr_fd("Invalid format : ./pipex infile cmd1 ", 2);
// ft_putendl_fd("cmd2 ... cmdn outfile", 2);