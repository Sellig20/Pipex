/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:08:06 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/05 22:43:50 by jecolmou         ###   ########.fr       */
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
        }
        i++;
    }
    return (NULL);
}

/*char	*ft_get_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			path = ft_split(env[i], " ");
		i++;
	}
	return (*path);
}

char	**ft_split_path(char **paths)
{
	char	**res;
	char	*path;
	int		i;

	i = 0;
	path = ft_get_path(paths);
	while (path[i])
	{
		res = ft_split(path, "=:");
		i++;
	}
	return (res);
}*/

void	ft_parent(t_data *x, char **argv, char **env)
{
	char	*pc;
	char	**option;

	pc = ft_path_command(argv[2], env);
	option = ft_get_command(argv[2], pc);
	x->child1 = fork();
	if (x->child1 < 0)
		return (perror("fork: "));
	if (x->child1 == 0)
		ft_child_one(x, pc, option, env);
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
		return (perror("fork: "));
	if (x->child2 == 0)
		ft_child_two(x, pc, option, env);
	else{
		waitpid(x->child2, NULL, 0);
		close(x->pipe_fd[0]);//on close 5
		close(x->f2);// on close 4
	}
	ft_free_array(option);
}

void	pipex(t_data *x, char **argv, char **env)
{
	if (pipe(x->pipe_fd) == -1)
		return (perror("pipe: "));
	ft_parent(x, argv, env);
}

int	main(int argc, char **argv, char **env)
{
	t_data	x;

	if (argc != 5)
		return (write(2, "Invalid number of arguments.\n", 27));
	x.f1 = ft_read_infile(argv[1]);
	if (x.f1 == -1)
	{
		ft_exist_error(argv[1]);
		return (EXIT_FAILURE);
	}
	x.f2 = ft_read_outfile(argv[4]);
	if (x.f2 < 0)
	{
		ft_exist_error(argv[1]);
		return (EXIT_FAILURE);
	}
	pipex(&x, argv, env);
	return (EXIT_SUCCESS);
}
