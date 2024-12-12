/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:02:21 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/12 19:02:17 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> //pour fork, execve, dup2, pipe, etc.
# include <fcntl.h> //pour open, O_RDONLY, O_WRONLY, etc.
# include <stdlib.h> //pour malloc, free, exit, etc.
# include <stdio.h> //pour perror, printf
# include <sys/wait.h> //pour wait, waitpid
# include "libft.h"

void    pipex(char *file1, char *cmd1, char *cmd2, char *file2, char **envp);

char	*get_path_from_envp(char **envp);
char	**split_path_directories(char *path_var);
char	*build_command_path(char *cmd, char *directory);
char	*find_command(char *cmd, char **envp);

void	free_array(char **array);

#endif