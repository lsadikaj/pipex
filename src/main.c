/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:31:17 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/18 17:10:32 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> //Pour exit()
#include "pipex.h" //Prototype de la fonction pipex
#include <fcntl.h> //Pour open(), O_WRONLY, O_CREAT, etc.
#include <unistd.h> //Pour close (), access(), STDOUT_FILENO, etc.

static void check_files(char *infile, char *outfile)
{
    if (access(infile, F_OK) == -1)
    {
        ft_printf("Error: Input file '%s' does not exist.\n", infile);
        exit(1);
    }
    if (access(infile, R_OK) == -1)
    {
        ft_printf("Error: No read permission for input file '%s'.\n", infile);
        exit(1);
    }
    if (open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 06440) < 0)
    {
        ft_printf("Error: Cannot create or write to output file '%s'.\n", outfile);
        exit(1);
    }
}

int main(int argc, char **argv, char **envp) 
{
    if (argc != 5)
    {
        ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
        return (1);
    }
    check_files(argv[1], argv[4]);
    pipex(argv[1], argv[2], argv[3], argv[4], envp);
    return (0);
}
