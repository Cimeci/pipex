/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:27 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/16 13:33:41 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

typedef struct s_pipex
{
	int		pipe_fd[2];
	pid_t	pid[2];
}			t_pipex;

char	*my_getenv(const char *name, char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j])
			j++;
		tmp = ft_substr(env[i], 0, 4);
		if (ft_strncmp(tmp, name, 4) == 0)
		{
			free(tmp);
			return (env[i] + j + 1);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

void	printf_double_char(char **str)
{
	int i;

	i = 0;
	while (str[i])
		printf("%s\n", str[i++]);
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

void	error_exit(const char *msg, t_pipex *pipex)
{
	perror(msg);
	free(pipex);
	exit(EXIT_FAILURE);
}

void ft_child_init(t_pipex *pipex, char *file, char *cmd, char **env)
{
	int infile;
	char *pathname;

	pipex->pid[0] = fork();
	if (pipex->pid[0] == -1)
		error_exit("Fork failed", pipex);
	if (pipex->pid[0] == 0) // Processus 1er enfant
	{
		infile = open(file, O_RDONLY);
		if (infile == -1)
			error_exit("Error opening infile", pipex);
		dup2(infile, STDIN_FILENO);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO); // Écrit dans le pipe
		close(infile);
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);

		pathname = find_path(env, cmd);
		if (!pathname)
			error_exit("Command not found", pipex);
		if (execve(pathname, ft_split(cmd, ' '), env) == -1)
			error_exit("Execve failed", pipex);
	}
}

void ft_child(t_pipex *pipex, char *file, char *cmd, char **env)
{
	int outfile;
	char *pathname;

	pipex->pid[1] = fork();
	if (pipex->pid[1] == -1)
		error_exit("Fork failed", pipex);
	if (pipex->pid[1] == 0) // enfants
	{
		outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			error_exit("Error opening outfile", pipex);
		dup2(pipex->pipe_fd[0], STDIN_FILENO); // Lit depuis le pipe
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);

		pathname = find_path(env, cmd);
		if (!pathname)
			error_exit("Command not found", pipex);
		if (execve(pathname, ft_split(cmd, ' '), env) == -1)
			error_exit("Execve failed", pipex);
	}
}

char *get_command(char **split)
{
	char *result;
	int i;
	char *tmp;

	i = 1;
	result = ft_strdup(ft_strrchr(split[0], '/') + 1);
	if (!result)
		return (NULL);
	while (split[i])
	{
		tmp = result;
		result = ft_strjoin(tmp, " ");
		free(tmp);
		tmp = NULL;
		tmp = result;
		result = ft_strjoin(tmp, split[i]);
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (result);
}

void	ft_adult(t_pipex *pipex, char **argv)
{
	char **split;
	int info_2;
	int info_3;

	info_2 = 0;
	info_3 = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_pipex *pipex;
	char **split;
	int info_2;
	int info_3;

	info_2 = 0;
	info_3 = 0;
	if (argc < 5)
	{
		printf("Usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n");
		return (EXIT_FAILURE);
	}
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		error_exit("Malloc failed", pipex);

	if (pipe(pipex->pipe_fd) == -1)
		error_exit("Pipe failed", pipex);

	split = ft_split(argv[2], ' ');
	if (!access(split[0], F_OK | X_OK))
	{
		argv[2] = get_command(split);
		info_2++;
	}
	ft_free(split);
	split = NULL;

	// premier processus
	ft_child_init(pipex, argv[1], argv[2], env);

	split = ft_split(argv[3], ' ');
	if (!access(split[0], F_OK | X_OK))
	{
		argv[3] = get_command(split);
		info_3++;
	}
	ft_free(split);
	// deuxieme processus
	ft_child(pipex, argv[argc - 1], argv[3], env);

	// Parent : Fermer les descripteurs et attendre les enfants
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pipex->pid[0], NULL, 0);
	waitpid(pipex->pid[1], NULL, 0);

	if (info_2 > 0)
		free(argv[2]);
	if (info_3 > 0)
		free(argv[3]);
	free(pipex);
	return (EXIT_SUCCESS);
}
