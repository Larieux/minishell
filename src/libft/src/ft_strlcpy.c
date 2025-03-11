/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:06:07 by mlarieux          #+#    #+#             */
/*   Updated: 2024/10/25 17:45:07 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
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
