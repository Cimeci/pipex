/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:27 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/16 15:40:46 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (!path_split)
		return (NULL);
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

// void ft_child_init(t_pipex *pipex, char *file, char *cmd, char **env)
// {
// 	int infile;
// 	char *pathname;

// 	pipex->pid[0] = fork();
// 	if (pipex->pid[0] == -1)
// 		error_exit("Fork failed", pipex);
// 	if (pipex->pid[0] == 0) // Processus 1er enfant
// 	{
// 		infile = open(file, O_RDONLY);
// 		if (infile == -1)
// 			error_exit("Error opening infile", pipex);
// 		dup2(infile, STDIN_FILENO);
// 		dup2(pipex->pipe_fd[1], STDOUT_FILENO); // Écrit dans le pipe
// 		close(infile);
// 		close(pipex->pipe_fd[0]);
// 		close(pipex->pipe_fd[1]);

// 		pathname = find_path(env, cmd);
// 		if (!pathname)
// 			error_exit("Command not found", pipex);
// 		if (execve(pathname, ft_split(cmd, ' '), env) == -1)
// 			error_exit("Execve failed", pipex);
// 	}
// }

// void ft_child(t_pipex *pipex, char *file, char *cmd, char **env)
// {
// 	int outfile;
// 	char *pathname;

// 	pipex->pid[1] = fork();
// 	if (pipex->pid[1] == -1)
// 		error_exit("Fork failed", pipex);
// 	if (pipex->pid[1] == 0) // enfants
// 	{
// 		outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (outfile == -1)
// 			error_exit("Error opening outfile", pipex);
// 		dup2(pipex->pipe_fd[0], STDIN_FILENO); // Lit depuis le pipe
// 		dup2(outfile, STDOUT_FILENO);
// 		close(outfile);
// 		close(pipex->pipe_fd[0]);
// 		close(pipex->pipe_fd[1]);

// 		pathname = find_path(env, cmd);
// 		if (!pathname)
// 			error_exit("Command not found", pipex);
// 		if (execve(pathname, ft_split(cmd, ' '), env) == -1)
// 			error_exit("Execve failed", pipex);
// 	}
// }

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

void close_unused_pipes(int i, int n, int **pipes)
{
    int j = 0;
    while (j < n - 1)
	{
        if (j != i - 1 && j != i)
		{
            close(pipes[j][0]);
            close(pipes[j][1]);
        }
        j++;
    }
}

int handle_child_process(int i, int n, char **argv, char **env, int **pipes, t_pipex *pipex)
{
    if (i == n) // Si on a traité tous les processus, on termine
        return 0;

    pipex->pid[i] = fork();
    if (pipex->pid[i] == -1)
        error_exit("Fork failed", pipex);

    if (pipex->pid[i] == 0)
	{ // Processus enfant
        if (i == 0)
		{ // Premier processus
            int infile = open(argv[1], O_RDONLY);
            if (infile == -1)
                error_exit("Error opening infile", pipex);
            dup2(infile, STDIN_FILENO);
            close(infile);
        }
		else
		{
            dup2(pipes[i - 1][0], STDIN_FILENO); // Lire depuis le pipe précédent
            close(pipes[i - 1][0]);
        }

        if (i == n - 1)
		{ // Dernier processus
            int outfile = open(argv[n], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (outfile == -1)
                error_exit("Error opening outfile", pipex);
            dup2(outfile, STDOUT_FILENO);
            close(outfile);
        }
		else
		{
            dup2(pipes[i][1], STDOUT_FILENO); // Écrire dans le pipe suivant
        }

        // Ferme tous les pipes non utilisés dans ce processus
        close_unused_pipes(i, n, pipes);

        char *pathname = find_path(env, argv[i + 2]);
        if (!pathname)
            error_exit("Command not found", pipex);
        if (execve(pathname, ft_split(argv[i + 2], ' '), env) == -1)
            error_exit("Execve failed", pipex);
    }

    // Appel récursif pour traiter le prochain enfant
    handle_child_process(i + 1, n, argv, env, pipes, pipex);
    return 0;
}

void close_parent_pipes(int **pipes, int n)
{
    int i = 0;
    while (i < n - 1)
{
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

void wait_for_children(int n, t_pipex *pipex)
{
    int i = 0;
    while (i < n)
	{
        waitpid(pipex->pid[i], NULL, 0);
        i++;
    }
}

int	main(int argc, char **argv, char **env)
{
	t_pipex *pipex;
	int i;
	int n;
	int **pipes;

	if (argc < 5)
	{
		printf("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n");
		return (EXIT_FAILURE);
	}
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		error_exit("Malloc failed", pipex);

	n = argc - 3;
	pipes = malloc(sizeof(int*) * (n - 1));
	i = 0;
	while (i < n - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
			error_exit("Pipe failed", pipex);
		i++;
	}

	// Création des processus enfants
	i = 0;
	while (i < n)
	{
		handle_child_process(i, n, argv, env, pipes, pipex);
		i++;
	}
	close_parent_pipes(pipes, n);
	wait_for_children(n, pipex);

	// Libération de mémoire
	i = 0;
	while (i < n)
		free(pipes[i++]);
	free(pipes);
	free(pipex);
	return (EXIT_SUCCESS);
}

