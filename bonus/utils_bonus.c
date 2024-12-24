/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:41:06 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/24 13:58:13 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_exit(int exit_nbr)
{
	if (exit_nbr == 1)
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
	exit(EXIT_FAILURE);
}

int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0644);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (in_or_out == 2)
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (ret == -1)
	{
		write(2, "pipex: Error opening file: ", 26);
		write(2, file, ft_strlen(file));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	return (ret);
}

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_env_var(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(name) + 1) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**args;

	i = -1;
	allpath = ft_split(get_env_var("PATH", env), ':');
	args = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, args[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_tab(args);
			return (exec);
		}
		free(exec);
	}
	free_tab(allpath);
	free_tab(args);
	return (cmd);
}
