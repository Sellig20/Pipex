/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:08:06 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/03 18:29:56 by jecolmou         ###   ########.fr       */
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

void	ft_parent(t_data *x, char **argv, char *env[])
{
	int	status;

	if (pipe(x->pipe_fd) == -1)
		return (perror("pipe: "));
	x->child1 = fork();
	if (x->child1 < 0)
		return (perror("fork: "));
	if (x->child1 == 0)
	{
		ft_child_one(x, argv[2], env);
		waitpid(x->child1, &status, 0);
	}
	close(x->pipe_fd[1]);
	close(x->f1);
	x->child2 = fork();
	if (x->child2 < 0)
		return (perror("fork: "));
	if (x->child2 == 0)
	{
		ft_child_two(x, argv[3], env);
		waitpid(x->child2, &status, 0);
	}
	close(x->pipe_fd[0]);
	close(x->f2);
}

void	pipex(t_data *x, char **argv, char *env[])
{
	ft_parent(x, argv, env);
}

int	main(int argc, char **argv, char *env[])
{
	t_data	x;

	if (argc != 5)
		return (write(2, "Invalid number of arguments.\n", 27));
	x.f1 = ft_read_infile(argv[1]);
	x.f2 = ft_read_outfile(argv[4]);
	if (x.f1 < 0 || x.f2 < 0)
		exit(EXIT_FAILURE);
	pipex(&x, argv, env);
	return (0);
}
