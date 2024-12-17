/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:48:50 by inowak--          #+#    #+#             */
/*   Updated: 2024/12/17 18:50:56 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    free_split(char **split)
{
    int i = 0;
    if (!split)
        return ;
    while (split[i])
        free(split[i++]);
    free(split);
}

void    error_exit(const char *msg, t_pipex *pipex)
{
    perror(msg);
    if (pipex && pipex->pipe_fd)
        free(pipex->pipe_fd);
    if (pipex && pipex->pids)
        free(pipex->pids);
    exit(EXIT_FAILURE);
}

char    *get_env_path(const char *name, char **env)
{
    int i = 0;
    while (env[i])
    {
        if (!ft_strncmp(env[i], name, ft_strlen(name)) && env[i][ft_strlen(name)] == '=')
            return (env[i] + ft_strlen(name) + 1);
        i++;
    }
    return (NULL);
}

char    *find_path(char *cmd, char **env)
{
    char **paths = ft_split(get_env_path("PATH", env), ':');
    char *full_path;
    int i = 0;

    if (!paths)
        return (NULL);
    while (paths[i])
    {
        full_path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
        if (!access(full_path, F_OK | X_OK))
        {
            free_split(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free_split(paths);
    return (NULL);
}

void    execute_command(char *cmd, char **env)
{
    char **args = ft_split(cmd, ' ');
    char *path;

    if (!args)
        exit(EXIT_FAILURE);
    path = find_path(args[0], env);
    if (!path)
    {
        free_split(args);
        perror("Command not found");
        exit(EXIT_FAILURE);
    }
    execve(path, args, env);
    perror("Execve failed");
    free(path);
    free_split(args);
    exit(EXIT_FAILURE);
}

void    setup_pipes(t_pipex *pipex)
{
    int i = 0;
    pipex->pipe_fd = malloc(sizeof(int) * 2 * (pipex->cmd_count - 1));
    if (!pipex->pipe_fd)
        error_exit("Pipe malloc failed", pipex);
    while (i < pipex->cmd_count - 1)
    {
        if (pipe(pipex->pipe_fd + (i * 2)) == -1)
            error_exit("Pipe creation failed", pipex);
        i++;
    }
}

void    close_pipes(t_pipex *pipex)
{
    int i = 0;
    while (i < 2 * (pipex->cmd_count - 1))
        close(pipex->pipe_fd[i++]);
}

void    child_process(t_pipex *pipex, char **argv, char **env, int i)
{
    if (i == 0 && dup2(pipex->infile, STDIN_FILENO) == -1)
        error_exit("Dup2 failed (infile)", pipex);
    if (i == pipex->cmd_count - 1 && dup2(pipex->outfile, STDOUT_FILENO) == -1)
        error_exit("Dup2 failed (outfile)", pipex);
    if (i > 0 && dup2(pipex->pipe_fd[(i - 1) * 2], STDIN_FILENO) == -1)
        error_exit("Dup2 failed (pipe read)", pipex);
    if (i < pipex->cmd_count - 1 && dup2(pipex->pipe_fd[i * 2 + 1], STDOUT_FILENO) == -1)
        error_exit("Dup2 failed (pipe write)", pipex);
    close_pipes(pipex);
    execute_command(argv[i + 2], env);
}

int main(int argc, char **argv, char **env)
{
    t_pipex pipex;
    int i = 0;

    if (argc < 5)
    {
        write(STDERR_FILENO, "Usage: ./pipex file1 cmd1 ... cmdn file2\n", 43);
        return (EXIT_FAILURE);
    }
    pipex.infile = open(argv[1], O_RDONLY);
    pipex.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex.infile < 0 || pipex.outfile < 0)
        error_exit("File open failed", &pipex);
    pipex.cmd_count = argc - 3;
    pipex.pids = malloc(sizeof(pid_t) * pipex.cmd_count);
    if (!pipex.pids)
        error_exit("PID malloc failed", &pipex);
    setup_pipes(&pipex);
    while (i < pipex.cmd_count)
    {
        pipex.pids[i] = fork();
        if (pipex.pids[i] < 0)
            error_exit("Fork failed", &pipex);
        if (pipex.pids[i] == 0)
            child_process(&pipex, argv, env, i);
        i++;
    }
    close_pipes(&pipex);
    i = 0;
    while (i < pipex.cmd_count)
        waitpid(pipex.pids[i++], NULL, 0);
    free(pipex.pipe_fd);
    free(pipex.pids);
    close(pipex.infile);
    close(pipex.outfile);
    return (EXIT_SUCCESS);
}
