/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:41:06 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/12 19:02:14 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Créer un pipe et gérer les erreurs
int create_pipe(int pipes[2])
{
    if (pipe(pipes) == -1)
    {
        perror("Pipe failed");
        exit(1);
    }
    return (pipes[0]); // Retourne l'entrée du pipe
}

// Fermer un descripteur de fichier de manière sécurisée
void close_fd(int fd)
{
    if (fd != -1)
    {
        close(fd);
    }
}

// Forker et exécuter un processus pour une commande donnée
void fork_and_execute(int input_fd, int output_fd, char *cmd, char **envp)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) // Processus enfant
    {
        handle_child(input_fd, output_fd, cmd, envp);
    }
    close(output_fd); // Ferme la sortie dans le parent
}
