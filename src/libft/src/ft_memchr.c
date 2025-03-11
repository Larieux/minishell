/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:54:41 by mlarieux          #+#    #+#             */
/*   Updated: 2024/10/25 17:43:57 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*chr;

	i = 0;
	chr = (unsigned char *) s;
	while (i < n)
	{
		if (chr[i] == (unsigned char)c % 256)
			return ((unsigned char *) s + i);
		i++;
	}
	return (NULL);
}
