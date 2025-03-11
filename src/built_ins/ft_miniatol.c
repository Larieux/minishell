/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_protecc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:21:46 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/15 16:52:17 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_sign(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

long	ft_atol_protecc(const char *s, int *error)
{
	int		i;
	int		sign;
	long	num;

	i = 0;
	num = 0;
	sign = 1;
	while (s && ((*(s + i) >= 9 && *(s + i) <= 13) || *(s + i) == 32))
		i++;
	if (s && (*(s + i) == '+' || *(s + i) == '-'))
		sign = get_sign(*(s + i++));
	while (*(s + i))
	{
		if (*(s + i) < '0' || *(s + i) > '9')
			return ((*error = 1, 0));
		if (sign == 1 && (num > LONG_MAX / 10
				|| (num == LONG_MAX / 10 && *(s + i) - '0' > LONG_MAX % 10)))
			return ((*error = 1, 0));
		if (sign == -1 && (-num < LONG_MIN / 10
				|| (-num == LONG_MIN / 10
					&& -(*(s + i) - '0') < LONG_MIN % 10)))
			return ((*error = 1), 0);
		num = 10 * num + (*(s + i++) - '0');
	}
	return ((*error = 0), (sign * num));
}
