/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:37:23 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/20 09:36:14 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_data	*ft_init_data(int argc, char **argv, char **env, t_pipex *pipex)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		free(pipex);
		exit(EXIT_FAILURE);
	}
	data->argc = argc;
	data->argv = argv;
	data->env = env;
	data->no_file = 0;
	data->allocated_cmds = malloc(sizeof(char *) * (argc - 3));
	if (!data->allocated_cmds)
	{
		free(data);
		free(pipex);
		exit(EXIT_FAILURE);
	}
	data->allocated_count = 0;
	return (data);
}

t_pipex	*init_pipex(int argc)
{
	t_pipex	*pipex;
	int		i;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		exit(EXIT_FAILURE);
	pipex->pipe_fd = malloc(sizeof(int) * 2 * (argc - 4));
	if (!pipex->pipe_fd)
	{
		free(pipex);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < argc - 4)
	{
		if (pipe(pipex->pipe_fd + 2 * i) == -1)
		{
			free(pipex->pipe_fd);
			free(pipex);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipex);
}
