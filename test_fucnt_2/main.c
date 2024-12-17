/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/12/17 08:38:38 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/17 08:38:38 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int	main(int argc, char **argv)
{
	if (argc != 3)
		return (0);

	int pipefd[2];
	if (pipe(pipefd) == -1)
	{
		perror("Pipe failed");
		return (0);
	}

	printf("Pipe créé avec pipefd[0] = %d (lecture) et pipefd[1] =
		%d (écriture)\n", pipefd[0], pipefd[1]);

	int fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
	{
		perror("ERROR fd1");
		return (0);
	}

	char *line;

	line = get_next_line(fd1);
	while (line)
	{
		if (line)
			write(pipefd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(fd1);
		if (!line)
			break ;
	}
	close(fd1);
	close(pipefd[1]);

	int fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd2 < 0)
	{
		perror("ERROR fd2");
		return (0);
	}

	char *buffer;
	ssize_t bytes_read = 1;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (bytes_read > 0)
	{
		bytes_read = read(pipefd[0], buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		if (bytes_read < 0)
		{
			perror("Read error");
			return (0);
		}
		write(fd2, buffer, bytes_read);
	}
	close(pipefd[0]);
	close(fd2);
	return (0);
}
