/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:49:45 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/18 11:29:54 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_puterror(int i)
{
	if (i == 1)
		perror("Error");
	if (i == 0)
		ft_putendl_fd("ERROR\n", 2);
	if (i == 2)
		ft_putendl_fd("Invalid format : ./pipex infile cmd1 cmd2 ... cmdn outfile\n", 2);
	exit(0);
}

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
		ft_printf("%s\n", str[i++]);
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

int	main(int argc, char **argv, char **env)
{
	if (argc < 4)
	{
		ft_printf("Error\n");
		return (0);
	}

	char *pathname_1 = find_path(env, argv[2]);
	char *pathname_2 = find_path(env, argv[3]);
	int pipe_fd[2];
	if (pipe(pipe_fd) == -1)
		ft_puterror();
	if (pathname_1 || pathname_2)
	{
		pipe_fd[1] = open(argv[1], O_RDONLY);
		if (pipe_fd[1] == -1)
			return (0);
		dup2(pipe_fd[1], STDIN_FILENO);
		close (pipe_fd[1]);
		pipe_fd[0] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipe_fd[0] == -1)
			return (0);
	    dup2(pipe_fd[0], STDOUT_FILENO);
    	close(pipe_fd[0]);
		execve(pathname_1, ft_split(argv[2], ' '), env);
		free(pathname_1);

		pipe_fd[1] = open(argv[4], O_RDONLY);
		if (pipe_fd[1] == -1)
			return (0);
		dup2(pipe_fd[1], STDIN_FILENO);
		close (pipe_fd[1]);
		execve(pathname_2, ft_split(argv[3], ' '), env);
		free(pathname_2);
	}
	free(pipe_fd);
}