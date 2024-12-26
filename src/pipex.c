/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:07:42 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/26 10:15:36 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args)
		exit(1);
	path = get_path(args[0], env);
	if (!path)
	{
		write(2, "pipex: ", 7);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Command not found\n", 20);
		free_tab(args);
		exit(127);
	}
	if (execve(path, args, env) == -1)
	{
		perror("execve");
		free_tab(args);
		exit(127);
	}
}

void	child(char **argv, int *p_fd, char **env)
{
	int	fd;

	close(p_fd[0]);
	fd = open_file(argv[1], 0);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(p_fd[1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	exec(argv[2], env);
}

void	parent(char **argv, int *p_fd, char **env, pid_t pid)
{
	int	fd;
	int	status;

	close(p_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(p_fd[0]);
		exit(WEXITSTATUS(status));
	}
	fd = open_file(argv[4], 1);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDOUT_FILENO);
	dup2(p_fd[0], STDIN_FILENO);
	close(fd);
	exec(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		exit(EXIT_FAILURE);
	}
	if (pipe(p_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child(argv, p_fd, env);
	parent(argv, p_fd, env, pid);
	return (0);
}
