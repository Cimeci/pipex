/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:44:19 by marvin            #+#    #+#             */
/*   Updated: 2024/12/17 20:07:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd, char **env)
{
	char	*pathname;

	pathname = find_path(env, cmd);
	if (!pathname)
		exit(EXIT_FAILURE);
	if (execve(pathname, ft_split(cmd, ' '), env) == -1)
		exit(EXIT_FAILURE);
}

char	*my_getenv(const char *name, char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j])
			j++;
		tmp = ft_substr(env[i], 0, j);
		if (ft_strncmp(tmp, name, j) == 0 && name[j] == '\0')
		{
			free(tmp);
			return (env[i] + j + 1);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

char	*find_path(char **env, char *cmd)
{
	char	**cmd_split;
	char	**path_split;
	char	*pathname;
	int		i;

	i = 0;
	path_split = ft_split(my_getenv("PATH", env), ':');
	cmd_split = ft_split(cmd, ' ');
	while (path_split[i])
	{
		cmd = ft_strjoin("/", cmd_split[0]);
		pathname = ft_strjoin(path_split[i], cmd);
		free(cmd);
		if (!access(pathname, F_OK | X_OK))
		{
			ft_free(path_split);
			ft_free(cmd_split);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	ft_free(path_split);
	ft_free(cmd_split);
	return (NULL);
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
		exit(EXIT_FAILURE);
	i = 0;
	while (i < argc - 4)
	{
		if (pipe(pipex->pipe_fd + 2 * i) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
	return (pipex);
}

void	close_pipes(t_pipex *pipex, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count * 2)
		close(pipex->pipe_fd[i++]);
}

void	process_child(t_pipex *pipex, int idx, int argc, char **argv, char **env)
{
	int	infile;
	int	outfile;

	if (idx == 0)
	{
		infile = open(argv[1], O_RDONLY);
		if (infile == -1)
			exit(EXIT_FAILURE);
		dup2(infile, STDIN_FILENO);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(infile);
	}
	else if (idx == argc - 4)
	{
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			exit(EXIT_FAILURE);
		dup2(pipex->pipe_fd[2 * (idx - 1)], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	else
	{
		dup2(pipex->pipe_fd[2 * (idx - 1)], STDIN_FILENO);
		dup2(pipex->pipe_fd[2 * idx + 1], STDOUT_FILENO);
	}
	close_pipes(pipex, argc - 4);
	execute_command(argv[idx + 2], env);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;
	int		i;

	if (argc < 5)
		return (EXIT_FAILURE);
	pipex = init_pipex(argc);
	i = 0;
	while (i < argc - 3)
	{
		pipex->pid[0] = fork();
		if (pipex->pid[0] == -1)
			exit(EXIT_FAILURE);
		if (pipex->pid[0] == 0)
			process_child(pipex, i, argc, argv, env);
		i++;
	}
	close_pipes(pipex, argc - 4);
	i = 0;
	while (i < argc - 3)
	{
		waitpid(pipex->pid[0], NULL, 0);
		i++;
	}
	free(pipex->pipe_fd);
	free(pipex);
	return (EXIT_SUCCESS);
}
