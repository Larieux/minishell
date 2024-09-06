/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:48:52 by jlarieux          #+#    #+#             */
/*   Updated: 2023/11/04 16:40:13 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	numcount(long nbr)
{
	size_t	i;

	i = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		i++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

void	ft_putnbr(long n, char *res, int csize)
{
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, res, csize - 1);
		res[csize - 1] = (n % 10) + '0';
	}
	if (n <= 9)
	{
		res[csize - 1] = n + '0';
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	size_t	csize;
	long	nbr;

	nbr = n;
	csize = numcount(nbr);
	if (n == 0)
		csize = 1;
	res = (char *)ft_calloc(sizeof(char), csize + 1);
	if (res == NULL)
		return (NULL);
	ft_putnbr(nbr, res, csize);
	return (res);
}
