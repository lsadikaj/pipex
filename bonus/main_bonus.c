/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:12:39 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/11 14:37:41 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int main(int argc, char **argv)
{
    char **commands;

    if (argc < 5)
    {
        fprintf(stderr, "Usage: ./pipex_bonus file1 cmd1 cmd2 ... cmdN file2\n");
        return (1);
    }
    commands = argv + 2; // Exclure file1 et file2
    pipex_bonus(argv[1], commands, argv[argc - 1]);
    return (0);
}
