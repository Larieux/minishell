/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:59:01 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 11:10:41 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	children(t_minist *minis, t_parser *parser_ptr, t_cmd role)
{
	int	code;

	if (role == CMD_FIRST)
		child(minis, parser_ptr);
	else if (role == CMD_LAST)
		child2(minis, parser_ptr);
	else
		inter_child(minis, parser_ptr);
	if (minis->err->code == ERR_ALLOC)
	{
		show_error(minis->err);
		code = minis->exit_code;
		free_minist();
		free(minis);
		exit(code);
	}
}

void	parent(t_minist *minis, t_cmd role)
{
	if (role == CMD_FIRST || role == CMD_INTER)
	{
		if (minis->exec->fd_pipe[PIPE_READ] != STDIN_FILENO
			&& minis->exec->fd_pipe[PIPE_READ] != -1)
			close(minis->exec->fd_pipe[PIPE_READ]);
	}
	if (role == CMD_INTER || role == CMD_LAST)
	{
		if (minis->exec->fd_prev_out != STDOUT_FILENO
			&& minis->exec->fd_prev_out != -1)
			close(minis->exec->fd_prev_out);
	}
}

void	do_fork(t_minist *minis, t_parser *parser_ptr, t_cmd role)
{
	bool	check_b_ins;

	parser_ptr->pid = -1;
	check_b_ins = check_built_ins(minis, parser_ptr, B_I_CHECK);
	if (check_b_ins == false)
		parser_ptr->pid = fork();
	if (parser_ptr->pid == 0 || check_b_ins == true)
		children(minis, parser_ptr, role);
	else if (parser_ptr->pid > 0)
		parent(minis, role);
	if (parser_ptr->pid == -1 && role == CMD_LAST
		&& minis->exec->fd_prev_out != STDOUT_FILENO
		&& minis->exec->fd_prev_out != -1)
		close(minis->exec->fd_prev_out);
}

void	do_pipe(t_minist *minis)
{
	int	code;

	if (pipe(minis->exec->fd_pipe) == -1)
	{
		set_show_error(minis->err, ERR_UNKNOWN, NULL);
		code = minis->exit_code;
		free_minist();
		free(minis);
		exit(code);
	}
}

void	do_pipex(t_minist *minis, t_parser *parser_ptr)
{
	while (parser_ptr->cmd_num >= 1)
	{
		if (parser_ptr->cmd_num == 1)
		{
			do_fork(minis, parser_ptr, CMD_LAST);
		}
		else if (parser_ptr->cmd_num == minis->exec->last_cmd)
		{
			do_pipe(minis);
			do_fork(minis, parser_ptr, CMD_FIRST);
			minis->exec->fd_prev_out = minis->exec->fd_pipe[PIPE_WRITE];
		}
		else
		{
			do_pipe(minis);
			do_fork(minis, parser_ptr, CMD_INTER);
			minis->exec->fd_prev_out = minis->exec->fd_pipe[PIPE_WRITE];
		}
		parser_ptr->cmd_num--;
		if (parser_ptr->left != NULL)
			parser_ptr = parser_ptr->left;
	}
}
