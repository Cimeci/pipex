/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:49:45 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/10 15:01:33 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_puterror()
{
	perror("Error");
	exit(0);
}

char *find_path(char **envp)
{
    int i = 0;

    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            return (envp[i] + 5); // Retourne la chaîne après "PATH="
        i++;
    }
    return (NULL); // PATH introuvable
}

char *check_command(char *cmd, char **envp)
{
    char *path = find_path(envp);
    char **paths;
    char *full_path;
    int i = 0;

    if (!path)
        return (NULL); // Pas de PATH dans les variables d'environnement
    paths = ft_split(path, ':'); // Découpe PATH en dossiers
	while (paths[i])
		ft_printf("%s\n", paths[i++]);
	i = 0;
    while (paths[i])
    {
        full_path = malloc(ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
        if (!full_path)
            return (NULL);
		sprintf(full_path, "%s/%s", paths[i], cmd);
		ft_printf("Here : \n%s\n", full_path);
        if (access(full_path, X_OK) == 0)
        {
			while (i > 0)
				free(paths[i--]);
            free(paths); // Libère les chemins
            return (full_path); // Retourne le chemin complet valide
        }
        free(full_path);
        i++;
    }
	while (i > 0)
		free(paths[i--]);
    free(paths);
    return (NULL); // Commande introuvable
}

void ft_check_file_and_commands(char **argv, char **envp)
{
    int fd1;
	int fd2;
	int i;	
	char *cmd_path;

    fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0)
        ft_puterror();
    close(fd1);

    fd2 = open(argv[4], O_WRONLY | O_CREAT, 0644);
    if (fd2 < 0)
        ft_puterror();
    close(fd2);
	i = 2;
    while (i <= 3)
    {
        cmd_path = check_command(argv[i], envp);
        if (!cmd_path)
			ft_puterror();
        free(cmd_path);
		i++;
    }
}


int main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		ft_printf("Error\n");
		return (0);
	}
	ft_check_file_and_commands(argv, envp);
	ft_printf("caca\n");
}