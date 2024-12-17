/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:12:16 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/17 14:26:27 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include "libft.h"

# define BUFFER_SIZE 256 

void    pipex_bonus(int argc, char **argv, char **envp);

char	*read_line(int fd);
void	read_here_doc(const char *limiter, int pipe_fd);
int		create_pipe(int pipes[2]);
void	close_fd(int fd);
void	fork_and_execute(int input_fd, int output_fd, char *cmd, char **envp);
void	handle_child(int input_fd, int output_fd, char *cmd, char **envp);
void	execute_pipeline(int infile, int outfile, char **commands, char **envp);

#endif
