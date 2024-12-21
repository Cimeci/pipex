/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:40:26 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/21 11:50:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	exec_command(char *pn, char **cmd_a, char **env)
{
	if (execve(pn, cmd_a, env) == -1 && execve(cmd_a[0], cmd_a, env) == -1)
	{
		free(pn);
		ft_free(cmd_a);
		perror("Error");
		return (0);
	}
	return (1);
}

static int	search_command_exec(char *cmd, char **env)
{
	char	*pn;
	char	**cmd_a;

	if (!ft_split(cmd, ' ')[0])
		exit(1);
	cmd_a = ft_split(cmd, ' ');
	if (!cmd_a)
		return (-1);
	if (!access(ft_split(cmd, ' ')[0], X_OK))
	{
		cmd = get_command(cmd_a);
		cmd_a = ft_split(cmd, ' ');
	}
	pn = find_path(env, cmd);
	if (!pn)
		return (-2);
	if (!exec_command(pn, cmd_a, env))
		return (0);
	else
	{
		ft_free(cmd_a);
		free(pn);
	}
	return (0);
}

static void	handle_to_first(t_pipex *pipex, t_data data, int fd)
{
	if (data.no_file == 0)
	{
		fd = open(data.argv[1], O_RDONLY);
		if (fd == -1)
			ft_free_error(pipex, &data);
		dup2(fd, STDIN_FILENO);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(fd);
	}
	else
	{
		dup2(0, STDIN_FILENO);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	}
}

static void	handle_to_first_last(t_pipex *pipex, int idx, t_data data)
{
	int	fd;

	fd = 0;
	if (idx == 0)
		handle_to_first(pipex, data, fd);
	else if (idx == data.argc - 4)
	{
		fd = open(data.argv[data.argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			ft_free_error(pipex, &data);
		dup2(pipex->pipe_fd[2 * (idx - 1)], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	process_child(t_pipex *pipex, int idx, t_data data)
{
	int	read_end;
	int	write_end;
	int	index_error;

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
	index_error = search_command_exec(data.argv[idx + 2], data.env);
	if (index_error == -1)
	{
		perror("Error3");
		exit(1);
	}
	else if (index_error == -2)
	{
		ft_putendl_fd("env: ‘’: No such file or directory", 2);
		exit(1);
	}
}
