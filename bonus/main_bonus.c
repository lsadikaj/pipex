/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:12:39 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/18 17:10:27 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
    if (ft_strncmp(argv[1], "here_doc", 8) == 0)
    {
        if (argc < 6)
        {
            ft_printf("Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file\n");
            return (1);
        }
    }
    else if (argc < 5)
    {
        ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
        return (1);
    }
    pipex_bonus(argc, argv, envp);
    return (0);
}
