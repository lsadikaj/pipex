/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:10:28 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/12 19:11:37 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void pipex_bonus(int argc, char **argv, char **envp) 
{
    int infile_pipe[2];
    int outfile;
    int i;

    if (ft_strncmp(argv[1], "here_doc", 8) == 0) 
    {
        if (argc < 5) 
        {
            ft_printf("Usage: ./pipex here_doc LIMITER cmd1 ... cmdn outfile\n");
            exit(1);
        }
        if (pipe(infile_pipe) == -1) 
        {
            perror("Error creating pipe");
            exit(1);
        }
        read_here_doc(argv[2], infile_pipe[1]);
        close(infile_pipe[1]); // Assurez-vous de fermer le pipe d'écriture
        i = 3;
        outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    } 
    else 
    {
        if (argc < 5) 
        {
            ft_printf("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n");
            exit(1);
        }
        infile_pipe[0] = open(argv[1], O_RDONLY); 
        if (infile_pipe[0] < 0) 
        {
            perror(argv[1]);
            exit(1);
        }
        i = 2;
        outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    if (outfile < 0) 
    {
        perror(argv[argc - 1]);
        exit(1);
    }

    // Appeler execute_pipeline avec le bon infile
    execute_pipeline(infile_pipe[0], outfile, &argv[i], envp);
}
