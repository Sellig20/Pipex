/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:34:59 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/05 22:43:35 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_array(char	**option)
{
	char	**tmp;

	if (!option)
		return ;
	tmp = option;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(option);
}

void	ft_argv_error(char *cmd)
{
	write(2, "zsh: command not found: ", 24);
	ft_putstr_fd(cmd, 2);
	write(2, "\n", 1);
}

int ft_exist_error(char *infile)
{
	write(2, "pipex: ", 7);
	write(2, "No such file or directory: ", 28);
	write(2, infile, ft_strlen(infile));
	write(2, "\n", 1);
	return (false);
}

int ft_perm_error(char *file)
{
	write(2, "pipex: ", 7);
	write(2, "permission denied: ", 19);
	write(2, file, ft_strlen(file));
	write(2, "\n", 1);
	return (false);
}

int ft_read_infile(char *infile)
{
	return (open(infile, O_RDONLY));
}

int ft_read_outfile(char *outfile)
{
	return (open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644));
}
