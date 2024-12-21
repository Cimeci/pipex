/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:44:19 by marvin            #+#    #+#             */
/*   Updated: 2024/12/21 14:40:03 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parent(t_pipex *pipex, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->argc - 3)
	{
		pipex->pid = fork();
		if (pipex->pid == -1)
			exit(EXIT_FAILURE);
		if (pipex->pid == 0)
		{
			process_child(pipex, i, *data);
			ft_free_all(pipex, data);
			exit(1);
		}
		data->no_file = 0;
		i++;
	}
	close_pipes(pipex, data->argc - 4);
	i = 0;
	while (wait(NULL) > 0)
		;
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;
	t_data	*data;

	if (argc != 5)
	{
		ft_putstr_fd("Invalid format : ./pipex infile cmd1 ", 2);
		ft_putendl_fd("cmd2 outfile", 2);
		exit(1);
	}
	pipex = init_pipex(argc);
	data = ft_init_data(argc, argv, env, pipex);
	check_input(data);
	parent(pipex, data);
	ft_free_all(pipex, data);
}
