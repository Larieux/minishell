/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:06:07 by jlarieux          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:05 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;

	i = 0;
	while ((i < n) && !((!src && !dest) && n))
	{
		*(unsigned char *)(dest + i) = *(const unsigned char *)(src + i);
		i++;
	}
	return (dest);
}
