/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 07:55:04 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/17 07:56:18 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
        printf("Je suis l'enfant ! Mon PID : %d\n", getpid());
    else
        printf("Je suis le parent ! Mon PID : %d, PID de l'enfant : %d\n", getpid(), pid);

    return 0;
}
