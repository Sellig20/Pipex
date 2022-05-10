/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:51:46 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/10 12:52:15 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parent(t_data *x, char **argv, char **env)
{
	char	*pc;
	char	**option;

	pc = ft_path_command(argv[2], env);
	option = ft_get_command(argv[2], pc);
	if (option == NULL)
		ft_free_array(option);
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
		waitpid(x->child1, NULL, 0);
		close(x->pipe_fd[1]);//close 6
		close(x->f1);// close 3
	}
	ft_free_array(option);
	pc = ft_path_command(argv[3], env);
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
		waitpid(x->child2, NULL, 0);
		close(x->pipe_fd[0]);//on close 5
		close(x->f2);// on close 4
	}
	ft_free_array(option);
}
