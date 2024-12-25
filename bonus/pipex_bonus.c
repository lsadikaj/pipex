/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:10:28 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/25 23:55:26 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	path = get_path(args[0], env);
	if (execve(path, args, env) == -1)
	{
		write(2, "pipex: ", 7);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Command not found\n", 20);
		free_tab(args);
		exit(EXIT_FAILURE);
	}
}

void	here_doc_put_in(char **av, int *p_fd)
{
	char	*ret;

	close(p_fd[0]);
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
		{
			free(ret);
			exit(0);
		}
		ft_putstr_fd(ret, p_fd[1]);
		free(ret);
	}
}

void	here_doc(char **argv)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		here_doc_put_in(argv, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	create_pipe(char *cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		exec(cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		fd_in;
	int		fd_out;

	if (argc < 5)
		handle_exit(1);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc") + 1) == 0)
	{
		if (argc < 6)
			handle_exit(1);
		i = 3;
		fd_out = open_file(argv[argc - 1], 2);
		here_doc(argv);
	}
	else
	{
		i = 2;
		fd_in = open_file(argv[1], 0);
		fd_out = open_file(argv[argc - 1], 1);
		dup2(fd_in, STDIN_FILENO);
	}
	while (i < argc - 2)
		create_pipe(argv[i++], env);
	dup2(fd_out, STDOUT_FILENO);
	exec(argv[argc - 2], env);
}
