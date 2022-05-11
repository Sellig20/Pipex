/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:51:46 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/11 17:36:37 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_annexe_parent_one(t_data *x)
{
	waitpid(x->child1, NULL, 0);
	close(x->pipe_fd[1]);
	close(x->f1);
}

void	ft_parent_one(t_data *x, char **argv, char **env)
{
	char	*pc;
	char	**option;

	pc = ft_path_command(argv[2], env);
	dprintf(2, "pc 1 = %s\n", pc);
	if (!pc)
		return ;
	option = ft_get_command(argv[2], pc);
	if (option == NULL)
		return ;
	x->child1 = fork();
	if (x->child1 < 0)
	{
		ft_free_array(option);
		free(pc);
		return (perror("fork: "));
	}
	if (x->child1 == 0)
		ft_child_one(x, pc, option, env);
	else
		ft_annexe_parent_one(x);
	ft_free_array(option);
	ft_parent_two(x, argv, env);
}

void	ft_annexe_parent_two(t_data *x)
{
	waitpid(x->child2, NULL, 0);
	close(x->pipe_fd[0]);
	close(x->f2);
}

void	ft_parent_two(t_data *x, char **argv, char **env)
{
	char	*pc;
	char	**option;

	pc = ft_path_command(argv[3], env);
	dprintf(2, "pc 2 = %s\n", pc);
	if (!pc)
		return ;
	option = ft_get_command(argv[3], pc);
	if (option == NULL)
		return ;
	x->child2 = fork();
	if (x->child2 < 0)
	{
		ft_free_array(option);
		free(pc);
		return (perror("fork: "));
	}
	if (x->child2 == 0)
		ft_child_two(x, pc, option, env);
	else
	{
		waitpid(x->child2, NULL, 0);
		close(x->pipe_fd[0]);
		close(x->f2);
	}
		ft_annexe_parent_two(x);
	ft_free_array(option);
}
