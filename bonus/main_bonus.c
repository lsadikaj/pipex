/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:12:39 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/12 19:02:05 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
    if (argc < 5)
    {
        fprintf(stderr, "Usage: ./pipex_bonus file1 cmd1 cmd2 ... cmdN file2\n");
        return (1);
    }
    pipex_bonus(argc, argv, envp);
    return (0);
}
