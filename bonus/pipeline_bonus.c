/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:46:57 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/17 15:38:56 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../includes/pipex.h"

// Redirige STDIN/STDOUT, ferme les descripteurs inutiles.
static void	setup_io(int input_fd, int output_fd)
{
	if (input_fd < 0 || output_fd < 0)
	{
		ft_printf("Invalid file descriptor\n");
		exit(1);
	}
	if (dup2(input_fd, STDIN_FILENO) == -1
		|| dup2(output_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		exit(1);
	}
	close(input_fd);
	close(output_fd);
}

// Valide la commande, découpe les arguments, retourne le chemin absolu.
static char	*get_valid_command(char *cmd, char **envp, char ***args)
{
	char	*cmd_path;

	if (!cmd || cmd[0] == '\0')
	{
		ft_printf("Empty command received\n");
		exit(127);
	}
	*args = ft_split(cmd, ' ');
	if (!(*args) || !(*args)[0])
	{
		ft_printf("Invalid command: '%s'\n", cmd);
		exit(127);
	}
	cmd_path = find_command((*args)[0], envp);
	if (!cmd_path)
	{
		ft_printf("Command not found: %s\n", (*args)[0]);
		free_array(*args);
		exit(127);
	}
	return (cmd_path);
}

// Configure l'IO, valide et exécute la commande avec execve.
void	handle_child(int input_fd, int output_fd, char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	setup_io(input_fd, output_fd);
	cmd_path = get_valid_command(cmd, envp, &args);
	execve(cmd_path, args, envp);
	perror("execve failed");
	free(cmd_path);
	free_array(args);
	exit(1);
}

// Crée des pipes et exécute les commandes en pipeline.
void	execute_pipeline(int infile, int outfile, char **commands, char **envp)
{
	int		pipes[2];
	int		prev_fd;
	int		i;

	prev_fd = infile;
	i = 0;
	while (commands[i + 1])
	{
		create_pipe(pipes);
		fork_and_execute(prev_fd, pipes[1], commands[i], envp);
		close_fd(pipes[1]);
		close_fd(prev_fd);
		prev_fd = pipes[0];
		i++;
	}
	fork_and_execute(prev_fd, outfile, commands[i], envp);
	close_fd(prev_fd);
	close_fd(outfile);
	while (wait(NULL) > 0)
		;
}
