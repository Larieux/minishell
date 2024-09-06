/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:46:07 by jlarieux          #+#    #+#             */
/*   Updated: 2024/02/23 16:34:17 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	lenlittle;

	i = 0;
	lenlittle = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *) big);
	while (big[i] && i + lenlittle <= len)
	{
		j = 0;
		while (big[i + j] == little[j] && little[j])
			j++;
		if (j == lenlittle)
			return ((char *) big + i);
		i++;
	}
	return (NULL);
}
