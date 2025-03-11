/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:21:01 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/15 14:19:26 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex(t_minist *minis)
{
	t_parser	*parser_ptr;
	int			status;

	parser_ptr = minis->parser;
	status = 0;
	if (init_pipex(minis) == -1)
		return (-1);
	while (parser_ptr && parser_ptr->right != NULL)
	{
		parser_ptr = parser_ptr->right;
		minis->exec->last_cmd++;
	}
	if (parser_ptr && parser_ptr != NULL)
	{
		set_signals(0);
		do_pipex(minis, parser_ptr);
		if (parser_ptr->pid > 0)
			status = wait_each_pid(minis);
		set_signals(1);
	}
	unlink ("/tmp/tmp_heredoc");
	return (status);
}
