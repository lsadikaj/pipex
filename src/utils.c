/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:01:03 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/25 15:55:48 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, O_RDONLY);
	else if (mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
	{
		ft_printf("pipex: Invalid mode for file: %s\n", file);
		exit(EXIT_FAILURE);
	}
	if (fd == -1)
	{
		ft_printf("pipex: Error opening file: %s\n", file);
		exit(EXIT_FAILURE);
	}
	return (fd);
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
		if (ft_strncmp(sub, name, ft_strlen(name)) == 0)
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
	char	*path_part;
	char	**all_path;
	char	**args;

	all_path = ft_split(get_env_var("PATH", env), ':');
	if (!all_path)
		return (NULL);
	args = ft_split(cmd, ' ');
	if (!args)
		return (free_tab(all_path), NULL);
	i = -1;
	while (all_path[++i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(path_part, args[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (free_tab(all_path), free_tab(args), exec);
		free(exec);
	}
	free_tab(all_path);
	free_tab(args);
	return (NULL);
}
