/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:21:17 by jlarieux          #+#    #+#             */
/*   Updated: 2024/01/20 15:23:15 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_snum(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (i);
}

char	**ft_free_res_split(char **res, int i)
{
	while (i > 0)
	{
		i--;
		free(res[i]);
	}
	free(res);
	return (0);
}

char	**ft_splitting(char const *s, char c, char **res, size_t snum)
{
	size_t	word;
	size_t	word_len;

	word = 0;
	word_len = 0;
	while (word < snum)
	{
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
		{
			s++;
			word_len++;
		}
		res[word] = (char *)ft_calloc(word_len + 1, sizeof(char));
		if (!res[word])
			return (ft_free_res_split(res, word));
		ft_strlcpy (res[word], (s - word_len), word_len + 1);
		word_len = 0;
		word++;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	snum;

	if (!s)
		return (NULL);
	snum = ft_snum(s, c);
	res = (char **)ft_calloc(snum + 1, sizeof(char *));
	if (!res)
		return (NULL);
	res = ft_splitting(s, c, res, snum);
	return (res);
}
