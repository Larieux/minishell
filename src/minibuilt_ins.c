/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibuilt_ins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:53:07 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/06 17:03:23 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_buitl_ins(t_minist *s_minis, int which)
{
	if (which == 0)
		ft_echo(s_minis->args[s_minis->arg_c + 1], 1);
	// else if (which == 1)
	// else if (which == 2)
	// else if (which == 3)
	// else if (which == 4)
	// else if (which == 5)
	// else if (which == 6)
	else
		return (0);
	return (1);
}

int	check_built_ins(t_minist *s_minis)
{
	static const char	*built_ins[8] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit"};
	int					built_in_len;
	int					arg_len;
	int					i;

	i = 0;
	built_in_len = ft_strlen(built_ins[i]);
	arg_len = ft_strlen(s_minis->args[s_minis->arg_c]);
	while (i <= 6 && !(arg_len == built_in_len
			&& ft_strncmp(s_minis->args[s_minis->arg_c],
				built_ins[i], built_in_len) == 0))
	{
		i++;
		built_in_len = ft_strlen(built_ins[i]);
	}
	if (exec_buitl_ins(s_minis, i))
		return (1);
	return (0);
}
