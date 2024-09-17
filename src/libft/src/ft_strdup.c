/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:57:48 by jlarieux          #+#    #+#             */
/*   Updated: 2023/10/27 14:57:51 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;

	ptr = malloc((ft_strlen(s) + 1) * sizeof (char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s, (ft_strlen(s) + 1));
	return (ptr);
}
