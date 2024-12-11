/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:10:28 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/11 14:47:58 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "libft.h"

// Ouvrir un fichier avec gestion des erreurs
static int open_file(char *file, int flags, int mode)
{
    int fd = open(file, flags, mode);
    if (fd < 0)
    {
        perror(file);
        exit(1);
    }
    return (fd);
}

// Exécuter une commande dans un processus enfant
static void execute_command(int input, int output, char *cmd)
{
    char    **args = ft_split(cmd, ' ');

    if (!command_path)
    {
        perror("Command not found");
        exit(127);
    }
    dup2(input, STDIN_FILENO);
    dup2(output, STDOUT_FILENO);
    close(input);
    close(output);
    execve(args[0], args, NULL);
    perror("Error executing command");
    exit(127);
}

// Gérer un processus dans le pipeline
static void handle_process(int input, int output, char *cmd)
{
    if (fork() == 0)
    {
        execute_command(input, output, cmd);
    }
}

// Configurer et exécuter le pipeline
static void execute_pipeline(int infile, int outfile, char **commands)
{
    int pipes[2];
    int prev_fd = infile;
    int i = 0;

    while (commands[i])
    {
        if (commands[i + 1])
        {
            if (pipe(pipes) == -1)
            {
                perror("Pipe failed");
                exit(1);
            }
            handle_process(prev_fd, pipes[1], commands[i]);
            close(pipes[1]);
            prev_fd = pipes[0];
        }
        else
        {
            handle_process(prev_fd, outfile, commands[i]);
            close(prev_fd);
        }
        i++;
    }
}

// Fonction principale orchestrant les pipes
void pipex_bonus(char *file1, char **commands, char *file2)
{
    int infile = open_file(file1, O_RDONLY, 0);
    int outfile = open_file(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    execute_pipeline(infile, outfile, commands);

    close(outfile);
    while (wait(NULL) > 0);
    close(infile);
}
