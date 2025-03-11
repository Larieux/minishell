/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:14:31 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/15 16:19:08 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**strdup_cmd(t_minist *minis, char **exp_value)
{
	char	**cmd;
	int		i;

	i = 0;
	while (exp_value && exp_value[i])
		i++;
	cmd = malloc((i + 1) * sizeof(char *));
	if (!cmd)
		return (set_error(minis->err, ERR_ALLOC, "strdup_cmd_1"), NULL);
	i = 0;
	while (exp_value && exp_value[i])
	{
		cmd[i] = ft_strdup(exp_value[i]);
		if (!cmd[i])
			return (cmd[i] = NULL, free_dtab(cmd)
				, set_error(minis->err, ERR_ALLOC, "strduo_cmd_2"), NULL);
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}
