/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:39:30 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/18 17:31:14 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_command(char **split)
{
	char	*result;
	int		i;
	char	*tmp;

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

void	check_input(t_data *data)
{
	int		i;
	char	**split;

	i = 2;
	while (i < data->argc - 2)
	{
		split = ft_split(data->argv[i], ' ');
		if (!access(split[0], F_OK | X_OK))
		{
			if (ft_strncmp(split[0], "./", 2))
				data->argv[i] = get_command(ft_split(data->argv[i], ' '));
		}
		ft_free(split);
		i++;
	}
	if (access(data->argv[1], F_OK | R_OK))
		ft_puterror(1);
	if (!access(data->argv[data->argc - 1], F_OK))
	{
		if (access(data->argv[data->argc - 1], W_OK))
			ft_puterror(1);
	}
}

static char	*my_getenv(const char *name, char **env)
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
