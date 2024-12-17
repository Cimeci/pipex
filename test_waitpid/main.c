/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 08:01:31 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/17 08:13:47 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid1 = fork();

    if (pid1 == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid1 == 0)
    {
        // Processus enfant 1
        printf("Je suis l'enfant 1 et je vais dormir 2 secondes.\n");
        sleep(2);
        printf("Enfant 1 terminé.\n");
        return (0);
    }
    else
    {
        pid_t pid2 = fork();

         if (pid2 == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid2 == 0)
    {
        // Processus enfant 1
        printf("Je suis l'enfant 2 et je vais dormir 3 secondes.\n");
        sleep(3);
        printf("Enfant 2 terminé.\n");
        return (0);
    }
    else
    {
        // Processus parent
        int status;
        printf("Le parent attend les enfants.\n");
        waitpid(pid1, &status, 0); // Attente
        printf("Le parent a fini d'attendre. Enfant 1 terminé\n");
        waitpid(pid2, &status, 0); // Attente
        printf("Le parent a fini d'attendre. Enfant 2 terminé\n");
    }

    return 0;
    }
}
