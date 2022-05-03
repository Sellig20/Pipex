/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:18:42 by jecolmou          #+#    #+#             */
/*   Updated: 2022/04/20 17:59:06 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_number_word(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (ft_is_charset(str[i], charset) && str[i])
			i++;
		if (!ft_is_charset(str[i], charset) && str[i])
		{
			count++;
			while (!ft_is_charset(str[i], charset) && str[i])
				i++;
		}
	}
	return (count);
}

int	ft_length_word(char *str, char *charset)
{
	int	i;
	int	wl;

	i = 0;
	wl = 0;
	while (ft_is_charset(str[i], charset) && str[i])
		i++;
	while (!ft_is_charset(str[i], charset) && str[i])
	{
		wl++;
		i++;
	}
	return (wl);
}

char	**ft_m_and_copy(char *str, char *charset, char **tab, int wc)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (j < wc)
	{
		k = 0;
		tab[j] = malloc(sizeof(char) * (ft_length_word(&str[i], charset) + 1));
		if (!tab[j])
			return (NULL);
		while (ft_is_charset(str[i], charset) && str[i])
			i++;
		while (!ft_is_charset(str[i], charset) && str[i])
		{
			tab[j][k] = str[i];
			k++;
			i++;
		}
		tab[j][k] = '\0';
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char *str, char *charset)
{
	int		wc;
	char	**tab;

	wc = ft_number_word(str, charset);
	tab = malloc(sizeof(char *) * (wc + 1));
	if (tab == NULL)
	{
		return (NULL);
	}
	tab = ft_m_and_copy(str, charset, tab, wc);
	return (tab);
}
