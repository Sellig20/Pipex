/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:52:14 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/05 22:44:38 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_command(char *cmd, char *pc)
{
	char	**command;
	char	*tmp;

	command = ft_split(cmd, " ");
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
	command = ft_split(cmd, " ");
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
	if (access(pc, X_OK) != 0)
			ft_argv_error(cmd);
	free(pc);
	return (NULL);
}

void ft_child_one(t_data *x, char *pc, char **option, char **env)
{
	close(x->f2);
	close(x->pipe_fd[IN]);
	if (x->f1 != STDIN_FILENO)
	{
		dup2(x->f1, STDIN_FILENO);
		close(x->f1);
	}
	if (x->pipe_fd[OUT] != STDOUT_FILENO)
	{
		dup2(x->pipe_fd[OUT], STDOUT_FILENO);
		close(x->pipe_fd[OUT]);
	}
	execve(pc, option, env);
	exit(127);
}

void ft_child_two(t_data *x, char *pc, char **option, char **env)
{
	if (x->pipe_fd[IN] != STDIN_FILENO)
	{
		dup2(x->pipe_fd[IN], STDIN_FILENO);
		close(x->pipe_fd[IN]);
	}
	if (x->f2 != STDOUT_FILENO)
	{
		dup2(x->f2, STDOUT_FILENO);
		close(x->f2);
	}
	execve(pc, option, env);
	exit(127);
}

/*if (f1 != 1)//fdin de la commande != 0
	{
		dup2 // dup2 fdin sur 0
	 	close(x->f1);
	}*/

/*	dprintf(2, "pc = %s\n", pc);
		dprintf(2, "option[0] = %s\n", option[0]);
		dprintf(2, "option[1] = %s\n", option[1]);
		dprintf(2, "option[2] = %s\n", option[2]);
	*/

/*if () // si fdout != 1
{
	dup2 // je dup2 fdout sur 1
	close(x->f2);
}*/
