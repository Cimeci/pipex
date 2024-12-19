/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:39:30 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/19 18:26:38 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	check_file(t_data *data)
{
	if (access(data->argv[1], F_OK | R_OK))
	{
		data->no_file = 1;
		perror("Error");
	}
	if (!access(data->argv[data->argc - 1], F_OK))
	{
		if (access(data->argv[data->argc - 1], W_OK))
			perror("Error");
	}
}

void	check_input(t_data *data)
{
	int		i;
	char	**split;

	check_file(data);
	i = 2;
	while (i < data->argc - 2)
	{
		split = ft_split(data->argv[i], ' ');
		if (!split[0])
			ft_putendl_fd("Error: Empty command", 2);
		else if (access(split[0], F_OK | X_OK))
			perror("Error");
		ft_free(split);
		i++;
	}
}
