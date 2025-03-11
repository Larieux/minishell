/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnrcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:46:07 by mlarieux          #+#    #+#             */
/*   Updated: 2024/10/26 10:06:52 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnrcmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	size_t			j;
	unsigned char	uc1;
	unsigned char	uc2;

	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	while (s1[i] && s2[j] && n > 0)
	{
		uc1 = (unsigned char)s1[i];
		uc2 = (unsigned char)s2[i];
		if (uc1 != uc2)
			return (uc1 - uc2);
		i--;
		j--;
		n--;
	}
	if (n == 0)
		return (0);
	uc1 = (unsigned char)s1[i];
	uc2 = (unsigned char)s2[i];
	return (uc1 - uc2);
}
