/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:52:14 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/03 14:23:10 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_child_one(int f1, int pipe_fd[2], char *cmd, char **env)
{
	char	**path;
	char	**command;
	char	*pc;
	int		i;

	path = ft_split_path(env);
	command = ft_split(cmd, " ");
	dup2(f1, STDIN_FILENO);
	close(pipe_fd[0]);
	i = 0;
	while (path[i])
	{
		pc = ft_strjoin(path[i], "/");
		pc = ft_strjoin(pc, command[0]);
		execve(pc, command, env);
		free(pc);
		i++;
	}
	execve(pc, command, env);
	exit(127);
}

void ft_child_two(int f2, int pipe_fd[2], char *cmd, char **env)
{
	char	**path;
	char	**command;
	char	*pc;
	int		i;
	i = 0;

	path = ft_split_path(env);
	command = ft_split(cmd, " ");
	dup2(f2, STDOUT_FILENO);
	close(pipe_fd[1]);
	i = 0;
	while (path[i])
	{
		pc = ft_strjoin(path[i], "/");
		pc = ft_strjoin(pc, command[0]);
		free (pc);
		i++;
	}
	execve(pc, command, env);
	exit(127);
}
