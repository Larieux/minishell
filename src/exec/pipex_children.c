/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:25:38 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 09:52:58 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_minist *minis, t_parser *parser_ptr)
{
	char	**cmd;

	check_for_io(minis, parser_ptr);
	dup_and_close(minis, CMD_FIRST);
	child_error(minis, parser_ptr);
	if (check_built_ins(minis, parser_ptr, B_I_EXECUTE) == false)
	{
		if (parser_ptr->exp_value && parser_ptr->exp_value[0])
			cmd = strdup_cmd(minis, parser_ptr->exp_value);
		else
			cmd = NULL;
		if (!cmd)
			return ;
		free_parser(minis);
		find_cmd(minis, cmd);
	}
}

void	inter_child(t_minist *minis, t_parser *parser_ptr)
{
	char	**cmd;

	check_for_io(minis, parser_ptr);
	dup_and_close(minis, CMD_INTER);
	child_error(minis, parser_ptr);
	if (check_built_ins(minis, parser_ptr, B_I_EXECUTE) == false)
	{
		if (parser_ptr->exp_value && parser_ptr->exp_value[0])
			cmd = strdup_cmd(minis, parser_ptr->exp_value);
		else
			cmd = NULL;
		if (!cmd)
			return ;
		free_parser(minis);
		find_cmd(minis, cmd);
	}
}

void	child2(t_minist *minis, t_parser *parser_ptr)
{
	char	**cmd;

	check_for_io(minis, parser_ptr);
	dup_and_close(minis, CMD_LAST);
	child_error(minis, parser_ptr);
	if (check_built_ins(minis, parser_ptr, B_I_EXECUTE) == false)
	{
		if (parser_ptr->exp_value && parser_ptr->exp_value[0])
			cmd = strdup_cmd(minis, parser_ptr->exp_value);
		else
			cmd = NULL;
		if (!cmd)
			return ;
		free_parser(minis);
		find_cmd(minis, cmd);
	}
}
