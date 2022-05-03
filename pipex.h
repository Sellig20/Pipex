/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:49:26 by jecolmou          #+#    #+#             */
/*   Updated: 2022/04/30 17:56:31 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

//////////LIBFT//////////
char	**ft_split(char *str, char *charset);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlen(const char *s);

//////////PIPEX//////////
char	*ft_get_path(char **env);
char	**ft_split_path(char **paths);

//////////TOOLS//////////
int ft_exist_error(char *infile);
int ft_perm_error(char *file);
int ft_read_infile(char *infile);
int ft_read_outfile(char *outfile);

//////////CHILDS FUNCTIONS//////////
void ft_child_one(int f1, int pipe_f[2], char *cmd, char **env);
void ft_child_two(int f2, int pipe_f[2], char *cmd, char **env);

#endif
