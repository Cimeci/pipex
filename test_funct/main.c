/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:27 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/12 17:08:37 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    pid_t p = fork();
    if(p<0){
      perror("fork fail");
      exit(0);
    }
    printf("Hello world!, process_id(pid) = %d \n",getpid());
    printf("hello\n");
    fork();
    fork();
    fork();
    return 0;
}