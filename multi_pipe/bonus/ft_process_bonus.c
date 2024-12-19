/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:40:26 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/19 11:19:07 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	execute_command(char *cmd, char **env)
{
	char	*pathname;
	char	**split;
	char	**cmd_args;

	split = ft_split(cmd, ' ');
	pathname = find_path(env, cmd);
	if (!pathname)
		pathname = ft_strdup(split[0]);
	cmd_args = ft_split(cmd, ' ');
	if (execve(pathname, cmd_args, env) == -1)
	{
		ft_free(split);
		ft_free(cmd_args);
		free(pathname);
		perror("Error");
	}
	else
	{
		ft_free(split);
		ft_free(cmd_args);
		free(pathname);
	}
}

static void	handle_to_first_last(t_pipex *pipex, int idx, t_data data)
{
	int	fd;

	if (idx == 0)
	{
		fd = open(data.argv[1], O_RDONLY);
		if (fd == -1)
			ft_puterror(1);
		dup2(fd, STDIN_FILENO);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(fd);
	}
	else if (idx == data.argc - 4)
	{
		fd = open(data.argv[data.argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(EXIT_FAILURE);
		dup2(pipex->pipe_fd[2 * (idx - 1)], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	process_child(t_pipex *pipex, int idx, t_data data)
{
	int	read_end;
	int	write_end;

	if (idx == 0 || idx == data.argc - 4)
		handle_to_first_last(pipex, idx, data);
	else
	{
		read_end = 2 * (idx - 1);
		write_end = 2 * idx + 1;
		dup2(pipex->pipe_fd[read_end], STDIN_FILENO);
		dup2(pipex->pipe_fd[write_end], STDOUT_FILENO);
	}
	close_pipes(pipex, data.argc - 4);
	execute_command(data.argv[idx + 2], data.env);
}
