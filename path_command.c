/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:50:50 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/10 12:52:01 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(char **env)
{
	int        i;
	char    **paths;

    i = 0;
    while (env[i])
    {
        if (ft_strnstr(env[i], "PATH=", 5))
        {
            paths = ft_split(env[i], "=:");
            return (paths);
			ft_free_array(paths);
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
	command = ft_split(cmd, " ");
	if (!command)
	{
		ft_free_array(command);
		return (NULL);
	}
	tmp = command[0];
	command[0] = pc;
	free(tmp);
	return (command);
}

char	*ft_path_command(char	*cmd, char **env)
{
	char	**path;
	char	**command;
	char	*pc;
	char	*tmp;
	int i;

	path = ft_get_path(env);
	if (path == NULL)
		ft_free_array(path);
	command = ft_split(cmd, " ");
	if (command == NULL)
		ft_free_array(command);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		pc = ft_strjoin(tmp, command[0]);
		free(tmp);
		if (access(pc, X_OK) == 0)
		{
			ft_free_array(command);
			ft_free_array(path);
			return (pc);
		}
		free(pc);
		i++;
	}
	ft_argv_error(cmd);
	ft_free_array(command);
	ft_free_array(path);
	return (strdup("fakepath"));
}
