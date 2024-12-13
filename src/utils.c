/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:01:03 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/13 23:55:21 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Trouver la variable PATH dans envp
char	*get_path_from_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

// Diviser PATH en répertoires
char	**split_path_directories(char *path_var)
{
	if (!path_var)
		return (NULL);
	return (ft_split(path_var, ':'));
}

// Construire le chemin complet et vérifier s'il est exécutable
char	*build_command_path(char *cmd, char *directory)
{
	char	*temp_path;
	char	*full_path;

	temp_path = ft_strjoin(directory, "/");
	full_path = ft_strjoin(temp_path, cmd);
	free(temp_path);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

// Libérer un tablerau de chaînes
void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// Rechercher la commande dans PATH
char	*find_command(char *cmd, char **envp)
{
	char	*path_var;
	char	**directories;
	char	*command_path;
	int		i;

	path_var = get_path_from_envp(envp);
	directories = split_path_directories(path_var);
	if (!directories)
		return (NULL);
	i = 0;
	while (directories[i])
	{
		command_path = build_command_path(cmd, directories[i]);
		if (command_path)
		{
			free_array(directories);
			return (command_path);
		}
		i++;
	}
	free_array(directories);
	return (NULL);
}
