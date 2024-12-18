/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:44:19 by marvin            #+#    #+#             */
/*   Updated: 2024/12/18 17:47:12 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;
	t_data	*data;
	int		i;

	if (argc < 5)
		ft_puterror(2);
	pipex = init_pipex(argc);
	data = ft_init_data(argc, argv, env, pipex);
	check_input(data);
	i = 0;
	while (i < argc - 3)
	{
		pipex->pid[0] = fork();
		if (pipex->pid[0] == -1)
			exit(EXIT_FAILURE);
		if (pipex->pid[0] == 0)
			process_child(pipex, i, *data);
		i++;
	}
	close_pipes(pipex, argc - 4);
	i = 0;
	while (wait(NULL) > 0)
		;
	free(pipex->pipe_fd);
	free(pipex);
	free(data);
	return (EXIT_SUCCESS);
}
