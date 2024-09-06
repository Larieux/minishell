/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:27:46 by jlarieux          #+#    #+#             */
/*   Updated: 2024/03/18 15:51:04 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat_gnl(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	res;

	i = 0;
	j = 0;
	res = 0;
	while (dst[i])
		i++;
	while (src[res])
		res++;
	if (size <= i)
		res += size;
	else
		res += i;
	while (i + 1 < size && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (res);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t		i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t size)
{
	size_t		i;

	if (!size)
		return (ft_strlen(src));
	i = 0;
	while (i < size - 1 && src [i])
	{
		dst [i] = src [i];
		i++;
	}
	dst [i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*res;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = malloc(size * sizeof (char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, ft_strlen(s1) + 1);
	ft_strlcat(res, s2, size);
	free(s1);
	return (res);
}
