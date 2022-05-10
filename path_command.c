/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:50:50 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/10 19:47:10 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(char **env)
{
	int		i;
	char	**paths;
	char	**tmp;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			tmp = ft_split(env[i], '=');
			if (!tmp)
				return (NULL);
			paths = ft_split(tmp[1], ':');
			ft_free_array(tmp);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	**ft_get_command(char *cmd, char *pc)
{
	char	**command;
	char	*tmp;

	if (!cmd || !pc)
		return (NULL);
	command = ft_split(cmd, ' ');
	if (!command)
	{
		free(pc);
		return (0);
	}
	dprintf(2, "command[0] === %s\n", command[0]);
	tmp = command[0];
	command[0] = pc;
		dprintf(2, "PC === %s\n", pc);

	free(tmp);
	return (command);
}

char *ft_return_pc(char **command, char **path, char *cmd)
{
	char	*pc;
	char	*tmp;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		pc = ft_strjoin(tmp, command[0]);
		free(tmp);
		if (access(pc, X_OK) == 0 || ft_strcmp(command[0], cmd) == 0)
		{
			ft_free_array(command);
			ft_free_array(path);
			return (pc);
		}
		free(pc);
		i++;
	}
	return (NULL);
}

char	*ft_path_command(char *cmd, char **env)
{
	char	**path;
	char	**command;
	char	*pc;

	if (!cmd || !env)
		return (NULL);
	path = ft_get_path(env);
	if (path == NULL)
		return (0);
	command = ft_split(cmd, ' ');
	if (command == NULL)
	{
		ft_free_array(path);
		return (0);
	}
	pc = ft_return_pc(command, path, cmd);
	if (pc != NULL || ft_strcmp(command[0], cmd) == 0)
		return (pc);
	ft_argv_error(cmd);
	ft_free_array(command);
	ft_free_array(path);
	return (NULL);
}
