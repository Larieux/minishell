/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:18:17 by jlarieux          #+#    #+#             */
/*   Updated: 2023/11/05 12:27:25 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int	*res;

	res = malloc(nmemb * size);
	if (res != NULL)
		ft_bzero(res, nmemb * size);
	else
		return (NULL);
	return (res);
}
