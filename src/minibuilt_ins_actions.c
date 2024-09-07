/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibuilt_ins_actions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:17:37 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/07 11:07:02 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(char *str, bool n)
{
	char	*res;
	char	*ptr;

	res = ft_strdup(str);
	if (n == true)
	{
		ptr = ft_strrchr(res, '\n');
		*ptr = '\0';
	}
	ft_putstr_fd(res, STDOUT_FILENO);
	return (free(res), 0);
}
