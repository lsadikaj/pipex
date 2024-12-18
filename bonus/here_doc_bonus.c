/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:48:06 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/18 17:10:29 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Lire une ligne à partir d'un descripteur de fichier
char *read_line(int fd) 
{
    char buffer[BUFFER_SIZE];
    char *line;
    char *temp;
    ssize_t bytes_read;

    line = NULL;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) 
    {
        buffer[bytes_read] = '\0';
        if (!line)
            line = ft_strdup(buffer);
        else
        {
            temp = line;
            line = ft_strjoin(line, buffer);
            free(temp);
        }
        if (ft_strchr(buffer, '\n')) 
            break;
    }
    return (line);
}

// Lire les entrées de here_doc et les écrire dans le pipe
void read_here_doc(const char *limiter, int pipe_fd) 
{
    char *line;

    while (1) 
    {
        write(STDOUT_FILENO, "> ", 2);
        line = read_line(STDIN_FILENO);
        if (!line)
            break ;
        if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
            && line[ft_strlen(limiter)] == '\n')
        {
            free(line);
            break;
        }
        write(pipe_fd, line, ft_strlen(line));
        free(line);
    }
    close(pipe_fd);
}
