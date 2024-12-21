/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:59:28 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/21 11:49:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command(char **split)
{
	char	*result;
	int		i;
	char	*tmp;

	i = 1;
	result = ft_strdup(ft_strrchr(split[0], '/') + 1);
	if (!result)
	{
		ft_free(split);
		return (NULL);
	}
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
	ft_free(split);
	return (result);
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

char	*find_pathname(char *cmd, char **cmd_split, char **path_split, int i)
{
	char	*pathname;

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
	return (NULL);
}

char	*find_path(char **env, char *cmd)
{
	char	**cmd_split;
	char	**path_split;
	char	*pathname;
	char	*tmp;
	int		i;

	i = 0;
	tmp = my_getenv("PATH", env);
	if (!tmp)
		return (NULL);
	if (ft_strncmp(cmd, "./", 2) == 0 || !access(cmd, X_OK))
		return (cmd);
	path_split = ft_split(tmp, ':');
	cmd_split = ft_split(cmd, ' ');
	while (path_split[i])
	{
		pathname = find_pathname(cmd, cmd_split, path_split, i);
		if (pathname)
			return (pathname);
		i++;
	}
	ft_free(path_split);
	ft_free(cmd_split);
	return (NULL);
}
