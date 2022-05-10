/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:51:46 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/10 17:19:49 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parent(t_data *x, char **argv, char **env)
{
	char	*pc;
	char	**option;
	int		status;

	status = 0;
	pc = ft_path_command(argv[2], env);
	if (!pc)
		return ;
	option = ft_get_command(argv[2], pc);
	if (option == NULL)
	{
		ft_free_array(option);
		return ;
	}
	x->child1 = fork();
	if (x->child1 < 0)
	{
		ft_free_array(option);
		free(pc);
		return (perror("fork: "));
	}
	if (x->child1 == 0)
	{
		ft_child_one(x, pc, option, env);
	}
	else
	{
		waitpid(x->child1, &status, 0);
		close(x->pipe_fd[1]);
		close(x->f1);
	}
	ft_free_array(option);
	pc = ft_path_command(argv[3], env);
	if (!pc)
		return ;
	option = ft_get_command(argv[3], pc);
	x->child2 = fork();
	if (x->child2 < 0)
	{
		ft_free_array(option);
		free(pc);
		return (perror("fork: "));
	}
	if (x->child2 == 0)
	{
		ft_child_two(x, pc, option, env);
	}
	else
	{
		waitpid(x->child2, &status, 0);
		close(x->pipe_fd[0]);
		close(x->f2);
	}
	ft_free_array(option);
}
