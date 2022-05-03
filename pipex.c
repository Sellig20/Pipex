/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:08:06 by jecolmou          #+#    #+#             */
/*   Updated: 2022/04/30 18:18:34 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_get_path(char **env)
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
}

void	pipex(int f1, int f2, char **argv, char *env[])
{
	pid_t	child1;
	pid_t	child2;
	int	status;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror("pipe: "));
	child1 = fork();
	if (child1 < 0)
		return (perror("fork: "));
	if (child1 == 0)
	{
		ft_child_one(f1, pipe_fd, argv[2], env);
		waitpid(child1, &status, 0);
	}
	child2 = fork();
	if (child2 < 0)
		return (perror("fork: "));
	if (child2 == 0)
	{
		ft_child_two(f2, pipe_fd, argv[3], env);
		waitpid(child2, &status, 0);
	}
}

int	main(int argc, char **argv, char *env[])
{
	int	f1;
	int	f2;

	if (argc != 5)
		return (write(2, "Invalid number of arguments.\n", 27));
	f1 = ft_read_infile(argv[1]);
	f2 = ft_read_outfile(argv[4]);
	if (f1 < 0 || f2 < 0)
		exit(EXIT_FAILURE);
	pipex(f1, f2, argv, env);
	return (0);
}
