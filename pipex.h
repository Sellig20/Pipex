/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:49:26 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/09 19:37:51 by jecolmou         ###   ########.fr       */
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
#include <stdbool.h>

# define IN 0
# define OUT 1

typedef struct s_data {
	int		pipe_fd[2];
	int		f1;
	int		f2;
	pid_t	child1;
	pid_t	child2;
}		t_data;

//////////LIBFT//////////
char	**ft_split(char *str, char *charset);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);

//////////PIPEX//////////
char	**ft_get_path(char **env);
char	**ft_split_path(char **paths);
void	ft_parent(t_data *x, char **argv, char *env[]);
void	pipex(t_data *x, char **argv, char *env[]);
char	*ft_path_command(char	*cmd, char **env);
char	**ft_get_command(char *cmd, char	*pc);

//////////TOOLS//////////
void	ft_argv_error(char *cmd);
int ft_exist_error(char *infile);
int ft_perm_error(char *file);
int ft_read_infile(char *infile);
int ft_read_outfile(char *outfile);
void	ft_free_array(char	**option);

//////////CHILDS FUNCTIONS//////////
void ft_child_one(t_data *x, char *pc, char **option, char **env);
void ft_child_two(t_data *x, char *pc, char **option, char **env);

#endif
