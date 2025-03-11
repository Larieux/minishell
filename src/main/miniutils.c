/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:55:16 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/13 19:01:15 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	str_alloc(t_minist *minis, char **str, char *msg, int size)
{
	*str = malloc(size);
	if (!*str)
		return (set_error(minis->err, ERR_ALLOC, msg), false);
	return (true);
}

t_minist	*get_minist(void)
{
	static t_minist	*minis = NULL;

	if (!minis)
	{
		minis = malloc(sizeof(t_minist));
		if (!minis)
			return (NULL);
		ft_memset(minis, 0, sizeof(t_minist));
	}
	return (minis);
}
