/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:07:42 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/18 18:15:03 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Ouvrir un fichier avec gestion des erreurs
static int open_file(char *file, int flags, int mode)
{
    int fd;

    // Si on utilise O_CREAT, garantir 0644 (permissions normales)
    if (flags & O_CREAT)
        mode = 0644;

    // Ouvrir/créer le fichier avec les bons flags et permissions
    fd = open(file, flags, mode);
    if (fd < 0)
    {
        ft_printf("Error: %s: %s\n", file, strerror(errno));
        exit(1);
    }
    return (fd);
}

// Exécuter une commande dans un processus enfant
static void execute_command(int input, int output, char *cmd, char **envp)
{
    char **args;
    char *cmd_path;

    args = ft_split(cmd, ' ');
    if (!args || !args[0])
    {
        ft_printf("Error: Invalid command '%s'\n", cmd);
        exit(127);
    }
    cmd_path = find_command(args[0], envp);
    if (!cmd_path)
    {
        ft_printf("Error: Command not found: '%s'\n", args[0]);
        free_array(args);
        exit(127);
    }
    dup2(input, STDIN_FILENO);
    dup2(output, STDOUT_FILENO);
    close(input);
    close(output);
    execve(cmd_path, args, envp); // Exécution de la commande
    perror("execve");
    free(cmd_path);
    free_array(args);
    exit(1);
}

// Gérer le premier processus
static void handle_first_process(int infile, int *fd, char *cmd, char **envp)
{
    if (fork() == 0)
    {
        close(fd[0]);
        execute_command(infile, fd[1], cmd, envp);
    }
}

// Gérer le deuxième processus
static void handle_second_process(int outfile, int *fd, char *cmd, char **envp)
{
    if (fork() == 0)
    {
        close(fd[1]);
        execute_command(fd[0], outfile, cmd, envp);
    }
}

// Fonction principale orchestrant les pipes
void pipex(char *file1, char *cmd1, char *cmd2, char *file2, char **envp)
{
    int fd[2];
    int infile;
    int outfile;

    infile = open_file(file1, O_RDONLY, 0);
    outfile = open_file(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipe(fd) == -1)
    {
        perror("Pipe failed");
        exit(1);
    }
    handle_first_process(infile, fd, cmd1, envp);
    close(fd[1]);
    handle_second_process(outfile, fd, cmd2, envp);
    close(fd[0]);

    wait(NULL);
    wait(NULL);

    close(infile);
    close(outfile);
}
