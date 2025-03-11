/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_args_van_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:41:27 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/13 19:28:16 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_van_cmd(t_minist *minis, char **cmd, char **van_cmd_args, int *i)
{
	van_cmd_args[1] = ft_strjoin(van_cmd_args[0], cmd[*i]);
	if (!(van_cmd_args[1]))
		return (set_error(minis->err, ERR_ALLOC, "join_van_cmd_1"), (void )0);
	free (van_cmd_args[0]);
	van_cmd_args[0] = ft_strjoin(van_cmd_args[1], " ");
	if (!van_cmd_args[0])
		return (set_error(minis->err, ERR_ALLOC, "join_van_cmd_2"), (void )0);
	free (van_cmd_args[1]);
	*i += 1;
}

char	*set_van_cmd_args(t_minist *minis, char **cmd)
{
	char	**van_cmd;
	char	*van_cmd_args;
	int		i;

	van_cmd = ft_split(cmd[0], '/');
	if (!van_cmd)
		return (set_error(get_minist()->err
				, ERR_ALLOC, "exec_van_cmd_1"), NULL);
	i = 0;
	while (van_cmd[i] != NULL)
		i++;
	if (i > 0)
		i--;
	van_cmd_args = ft_strjoin(van_cmd[i], " ");
	if (!(van_cmd_args))
		return (free_dtab(van_cmd)
			, set_error(minis->err, ERR_ALLOC, "exec_van_cmd_2"), NULL);
	free_dtab (van_cmd);
	return (van_cmd_args);
}

void	exec_vanilla_cmd(t_minist *minis, char **env, char **cmd)
{
	char	**van_cmd;
	char	*van_cmd_args[2];
	int		i;

	van_cmd_args[0] = set_van_cmd_args(minis, cmd);
	if (!van_cmd_args[0])
		return ;
	i = 1;
	while (cmd && cmd[i])
		join_van_cmd(minis, cmd, van_cmd_args, &i);
	if (!van_cmd_args[0])
		return ;
	van_cmd = ft_split(van_cmd_args[0], ' ');
	if (!van_cmd)
		return (free(van_cmd_args[0])
			, set_error(minis->err, ERR_ALLOC, "exec_van_cmd_4"), (void )0);
	free (van_cmd_args[0]);
	if (cmd && cmd[0])
		execve(cmd[0], van_cmd, env);
	free_dtab (van_cmd);
}
