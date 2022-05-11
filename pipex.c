/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:08:06 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/11 12:46:42 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_data *x, char **argv, char **env)
{
	if (pipe(x->pipe_fd) == -1)
		return (perror("pipe: "));
	ft_parent_one(x, argv, env);
}

int	main(int argc, char **argv, char **env)
{
	t_data	x;
	int i;

	i = 0;
	if (argc != 5)
		return (write(2, "Invalid number of arguments.\n", 27));
	while(argv[i])
	{
		if (argv[2][i] == '\0' || ft_strlen(argv[i]) == 0
		|| argv[3][i] == '\0' || ft_strlen(argv[i]) == 0)
		{
			ft_argv_error(NULL);
			return (1);
		}
		i++;
	}
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
