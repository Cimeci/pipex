/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:40:47 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/18 15:08:17 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_puterror(int i)
{
	if (i == 1)
		perror("Error");
	if (i == 0)
		ft_putendl_fd("ERROR", 2);
	if (i == 2)
	{
		ft_putstr_fd("Invalid format : ./pipex infile cmd1 ", 2);
		ft_putendl_fd("cmd2 ... cmdn outfile", 2);
	}
	exit(0);
}

void	close_pipes(t_pipex *pipex, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count * 2)
		close(pipex->pipe_fd[i++]);
}
