/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:24:38 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 09:37:06 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_here_doc(t_minist *minis)
{
	t_parser	*parser_ptr;
	t_inout		*io;

	io = NULL;
	parser_ptr = NULL;
	if (minis->parser)
		parser_ptr = minis->parser;
	while (parser_ptr)
	{
		if (parser_ptr && parser_ptr->io)
			io = parser_ptr->io;
		while (io && io->type && io->type == IO_HEREDOC)
		{
			minis->exec->eof_len = ft_strlen(io->value);
			init_heredoc(minis, io);
			io = io->next;
		}
		parser_ptr = parser_ptr->right;
	}
}

int	init_pipex(t_minist *minis)
{
	if (!minis->exec || minis->exec == NULL)
		minis->exec = malloc(sizeof(t_exec));
	if (!minis->exec)
		return (-1);
	minis->exec->fd_pipe[PIPE_READ] = STDIN_FILENO;
	minis->exec->fd_pipe[PIPE_WRITE] = STDOUT_FILENO;
	minis->exec->fd_in = STDIN_FILENO;
	minis->exec->fd_out = STDOUT_FILENO;
	minis->exec->fd_prev_out = STDOUT_FILENO;
	minis->exec->last_cmd = 1;
	check_here_doc(minis);
	return (0);
}

int	wait_each_pid(t_minist *minis)
{
	t_parser	*parser;
	int			status;

	status = 0;
	parser = minis->parser;
	while (parser && parser->right != NULL)
		parser = parser->right;
	if (parser && parser->pid && parser->pid > 0)
	{
		waitpid(parser->pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	parser = parser->left;
	while (parser != NULL)
	{
		if (parser && parser->pid && parser->pid > 0)
			waitpid(parser->pid, NULL, 0);
		parser = parser->left;
	}
	return (status);
}
