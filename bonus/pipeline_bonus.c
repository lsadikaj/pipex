/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:46:57 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/12 19:15:13 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Gérer un processus enfant pour une commande donnée
void	handle_child(int input_fd, int output_fd, char *cmd, char **envp)
{
    char *argv[] = {"/bin/sh", "-c", cmd, NULL};

    if (dup2(input_fd, STDIN_FILENO) == -1 || dup2(output_fd, STDOUT_FILENO) == -1)
    {
        perror("dup2 failed");
        exit(1);
    }
    close(input_fd);
    close(output_fd);

    // Remplace l'appel à execute_command par execve
    if (execve(argv[0], argv, envp) == -1)
    {
        perror("execve failed");
        exit(1);
    }
}

// Exécuter un pipeline complet avec plusieurs commandes
void	execute_pipeline(int infile, int outfile, char **commands, char **envp)
{
    int pipes[2];
    int prev_fd;
    int i;

    prev_fd = infile; // Initialise avec infile
    i = 0;
    while (commands[i + 1]) // Toutes les commandes sauf la dernière
    {
        pipes[0] = create_pipe(pipes);
        fork_and_execute(prev_fd, pipes[1], commands[i], envp);
        close_fd(prev_fd); // Ferme l'entrée précédente
        prev_fd = pipes[0]; // Prépare le prochain fichier d'entrée
        i++;
    }
    // Dernière commande
    fork_and_execute(prev_fd, outfile, commands[i], envp);
    close_fd(prev_fd);
    close_fd(outfile);
    while (wait(NULL) > 0)
	{
		// Attente de la fin de tous les processus enfants
	}
}
