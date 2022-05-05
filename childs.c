/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:52:14 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/04 18:41:07 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_child_one(t_data *x, char *cmd, char **env)
{
	char	**path;
	char	**command;
	char	*pc;
	int i;

	i = 0;
	path = ft_get_path(env);
	command = ft_split(cmd, " ");
	dprintf(2, "x-fd[%d] = %d\nx->f2 = %d\n", 0, x->f2, x->f2);
	dup2(x->f1, STDIN_FILENO);
	dup2(x->pipe_fd[1], STDOUT_FILENO);
	close(x->pipe_fd[0]);
	close(x->f1);
	if (access(pc, X_OK) != 0)
		return (ft_argv_error(cmd));
}

void ft_child_two(t_data *x, char *cmd, char **env)
{
	char	**path;
	char	**command;
	char	*pc;
	int i;

	i = 0;
	path = ft_get_path(env);
	command = ft_split(cmd, " ");
	dprintf(2, "x-fd[%d] = %d\nx->f2 = %d\n", 0, x->f2, x->f2);
	close(x->pipe_fd[1]);
	dup2(x->pipe_fd[0], STDIN_FILENO);
	dup2(x->f2, STDOUT_FILENO);
	close(x->pipe_fd[0]);
	close(x->f2);
	execve(pc, command, env);
	if (access(pc, X_OK) != 0)
		return (ft_argv_error(cmd));
}



char	*ft_path_command(char	*cmd, char **env)
{
	char	**path;
	char	**command;
	char	*pc;

	path = ft_get_path(env);
	command = ft_split(cmd, " ");
	while (path[i])//ACCESS
	{
		pc = ft_strjoin(path[i], "/");
		pc = ft_strjoin(pc, command[0]);
		if (access(pc, X_OK) == 0)
			return (pc);
		else
			return (ft_argv_error(cmd));
		i++;
	}
	free(pc);
	return (NULL);
}

void ft_child(t_data *x, char *cmd, char **option, char **env)
{
	//avant je veux les dup2 si les fd ne sont pas les bon
	 if ()//fdin de la commande != 0
	 {
		dup2 // dup2 fdin sur 0
	 	close(x->f1);
	 }
	 if () // si fdout != 1
	 {
	 	dup2 // je dup2 fdout sur 1
	 	close(x->f2);
	 }
	execve(cmd, option, env);
	return ;
}
