/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:27 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/12 23:41:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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

void	error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
	{
		fprintf(stderr, "Usage: ./pipex infile cmd1 cmd2 outfile\n");
		return (EXIT_FAILURE);
	}

	int pipe_fd[2];
	if (pipe(pipe_fd) == -1)
		error_exit("Pipe failed");

	// Fork pour le premier processus
	pid_t pid1 = fork();
	if (pid1 == -1)
		error_exit("Fork failed");

	if (pid1 == 0) // Processus enfant 1
	{
		int infile = open(argv[1], O_RDONLY);
		if (infile == -1)
			error_exit("Error opening infile");
		dup2(infile, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO); // Écrit dans le pipe
		close(infile);
		close(pipe_fd[0]);
		close(pipe_fd[1]);

		char *pathname_1 = find_path(env, argv[2]);
		if (!pathname_1)
			error_exit("Command not found");
		execve(pathname_1, ft_split(argv[2], ' '), env);
		error_exit("Execve failed");
	}

	// Fork pour le deuxième processus
	pid_t pid2 = fork();
	if (pid2 == -1)
		error_exit("Fork failed");

	if (pid2 == 0) // Processus enfant 2
	{
		int outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			error_exit("Error opening outfile");
		dup2(pipe_fd[0], STDIN_FILENO); // Lit depuis le pipe
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		close(pipe_fd[0]);
		close(pipe_fd[1]);

		char *pathname_2 = find_path(env, argv[3]);
		if (!pathname_2)
			error_exit("Command not found");
		execve(pathname_2, ft_split(argv[3], ' '), env);
		error_exit("Execve failed");
	}

	// Parent : Fermer les descripteurs et attendre les enfants
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (EXIT_SUCCESS);
}
