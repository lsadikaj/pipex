/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:31:17 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/12 19:02:20 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //Pour fprintf(), perror()
#include <stdlib.h> //Pour exit()
#include "pipex.h" //Prototype de la fonction pipex
#include <fcntl.h> //Pour open(), O_WRONLY, O_CREAT, etc.
#include <unistd.h> //Pour close (), access(), STDOUT_FILENO, etc.

int main(int argc, char **argv, char **envp) 
{
    if (argc != 5) {
        fprintf(stderr, "Usage: ./pipex file1 cmd1 cmd2 file2\n");
        return (1);
    }

    // Étape 1 : Vérifier l'accès aux fichiers
    if (access(argv[1], F_OK) == -1) {
        perror("Error: file1");
        return (1);
    }

    int outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile < 0) {
        perror("Error: file2");
        return (1);
    }
    close(outfile);

    // Étape 2 : Appeler la fonction principale du projet (pipex)
    pipex(argv[1], argv[2], argv[3], argv[4], envp);

    return (0);
}
