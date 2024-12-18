/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:10:28 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/18 17:10:23 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	handle_here_doc(char **argv, int *infile_pipe)
{
	if (pipe(infile_pipe) == -1)
	{
		perror("Error creating pipe");
		exit(1);
	}
	read_here_doc(argv[2], infile_pipe[1]);
	close(infile_pipe[1]);
}

static int open_outfile(char *filename, int append)
{
    int outfile;

    if (append)
        outfile = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (outfile < 0)
    {
        ft_printf("./pipex_bonus: %s: ", filename);
        perror(NULL); // Affiche directement l'erreur système
        exit(1);
    }
    return (outfile);
}

static int	setup_infile(char *filename)
{
	int infile;

	infile = open(filename, O_RDONLY);
	if (infile < 0)
	{
		ft_printf("Error: Cannot open input file '%s'\n", filename);
		perror(NULL);
		exit(1);
	}
	return (infile);
}

void	pipex_bonus(int argc, char **argv, char **envp)
{
	int	infile_pipe[2];
	int	outfile;
	int	i;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 5)
			ft_printf("Usage: ./pipex here_doc LIMITER cmd1 ... cmdn outfile\n");
		handle_here_doc(argv, infile_pipe);
		i = 3;
		outfile = open_outfile(argv[argc - 1], 1);
	}
	else
	{
		if (argc < 5)
			ft_printf("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n");
		infile_pipe[0] = setup_infile(argv[1]);
		i = 2;
		outfile = open_outfile(argv[argc - 1], 0);
	}
	argv[argc - 1] = NULL;
	execute_pipeline(infile_pipe[0], outfile, &argv[i], envp);
}
