/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:49:45 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/11 18:30:25 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_puterror(void)
{
	perror("Error");
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

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
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
	if (argc < 2)
	{
		ft_printf("Error\n");
		return (0);
	}
	char *result = my_getenv("PATH", env);
	char *pathname = find_path(env, argv[1]);
	if (result && pathname)
	{
		// ft_printf("My getenv :\n");
		// ft_printf("%s\n", result);
		// ft_printf("\n");
		// ft_printf("Find Path :\n");
		// ft_printf("%s\n", pathname);
		execve(pathname, ft_split(argv[1], ' '), env);
		free(pathname);
	}
}