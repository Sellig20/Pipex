/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:20:47 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/10 11:21:03 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s;

	s = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (s == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = (char)s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
