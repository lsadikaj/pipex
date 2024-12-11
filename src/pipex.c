/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:07:42 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/11 13:51:49 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "pipex.h"
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
    char **args = ft_split(cmd, ' ');
    if (!args)
    {
        perror("Error splitting command");
        exit(1);
    }
    dup2(input, STDIN_FILENO);
    dup2(output, STDOUT_FILENO);
    close(input);
    close(output);
    execve(args[0], args, NULL); // Utilise l'environnement par défaut
    perror("Error executing command");
    exit(127);
}

// Gérer le premier processus
static void handle_first_process(int infile, int *fd, char *cmd)
{
    if (fork() == 0)
    {
        close(fd[0]);
        execute_command(infile, fd[1], cmd);
    }
}

// Gérer le deuxième processus
static void handle_second_process(int outfile, int *fd, char *cmd)
{
    if (fork() == 0)
    {
        close(fd[1]);
        execute_command(fd[0], outfile, cmd);
    }
}

// Fonction principale orchestrant les pipes
void pipex(char *file1, char *cmd1, char *cmd2, char *file2)
{
    int fd[2];
    int infile = open_file(file1, O_RDONLY, 0);
    int outfile = open_file(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(1);
    }
    handle_first_process(infile, fd, cmd1);
    close(fd[1]);
    handle_second_process(outfile, fd, cmd2);
    close(fd[0]);

    wait(NULL);
    wait(NULL);

    close(infile);
    close(outfile);
}
