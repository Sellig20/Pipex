/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:34:59 by jecolmou          #+#    #+#             */
/*   Updated: 2022/04/30 15:45:14 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



int ft_exist_error(char *infile)
{
    write(2, "pipex: ", 7);
    write(2, "No such file or directory: ", 28);
    write(2, infile, ft_strlen(infile));
    write(2, "\n", 1);
        return (-1);
}

int ft_perm_error(char *file)
{
    write(2, "pipex: ", 7);
    write(2, "permission denied: ", 19);
    write(2, file, ft_strlen(file));
    write(2, "\n", 1);
    return (-1);
}

int ft_read_infile(char *infile)
{
    if (access(infile, F_OK) == -1)
        return (ft_exist_error(infile));
    else if (access(infile, R_OK) == -1)
        return (ft_perm_error(infile));
    else
        return (open(infile, O_RDONLY));
}

int ft_read_outfile(char *outfile)
{
    if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
        return (ft_perm_error(outfile));
    else
        return (open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644));
}