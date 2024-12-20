/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:40:26 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/20 09:43:42 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	exec_bef_path(char *cmd, char **env, char **cmd_args, char **split)
{
	if (execve(cmd, ft_split(get_command(cmd_args), ' '), env) == -1)
	{
		ft_free(split);
		ft_free(cmd_args);
		perror("Error");
		return (0);
	}
	return (1);
}

// pn -> pathname //
// cmd_a -> cmd_args //

static int	execute_command(char *cmd, char **env)
{
	char	*pn;
	char	**split;
	char	**cmd_a;

	if (!ft_split(cmd, ' ')[0])
		exit(1);
	split = ft_split(cmd, ' ');
	if (!split)
		return (-1);
	pn = find_path(env, cmd);
	if (!pn)
		return (-2);
	cmd_a = ft_split(cmd, ' ');
	if (execve(pn, cmd_a, env) == -1 && execve(cmd_a[0], cmd_a, env) == -1)
	{
		if (!exec_bef_path(cmd, env, cmd_a, split))
			free(pn);
	}
	else
	{
		ft_free(split);
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
	index_error = execute_command(data.argv[idx + 2], data.env);
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
