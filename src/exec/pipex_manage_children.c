/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_manage_children.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:34:23 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/15 16:18:50 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_child_first(t_minist *minis)
{
	int	fd1;
	int	fd2;
	int	fd3;

	fd1 = 0;
	fd2 = 0;
	fd3 = 0;
	if (minis->exec->fd_pipe[PIPE_READ] != STDIN_FILENO)
		fd1 = dup_and_close_pipes(minis, PIPE_READ);
	if (minis->exec->fd_in != STDIN_FILENO)
		fd2 = dup_and_close_redir(minis, READ);
	if (minis->exec->fd_out != STDOUT_FILENO)
		fd3 = dup_and_close_redir(minis, WRITE);
	if (minis->exec->fd_pipe[PIPE_WRITE] != STDOUT_FILENO)
		close_unused(minis, PIPE_WRITE);
	check_fd(fd1, fd2, fd3, 0);
}

void	manage_child_last(t_minist *minis)
{
	int	fd1;
	int	fd2;
	int	fd3;

	fd1 = 0;
	fd2 = 0;
	fd3 = 0;
	if (minis->exec->fd_prev_out != STDOUT_FILENO)
		fd1 = dup_and_close_pipes(minis, PIPE_WRITE);
	if (minis->exec->fd_in != STDIN_FILENO)
		fd2 = dup_and_close_redir(minis, READ);
	if (minis->exec->fd_out != STDOUT_FILENO)
		fd3 = dup_and_close_redir(minis, WRITE);
	if (minis->exec->fd_pipe[PIPE_READ] != STDIN_FILENO)
		close_unused(minis, PIPE_READ);
	check_fd(fd1, fd2, fd3, 0);
}

void	manage_child_inter(t_minist *minis)
{
	int	fd1;
	int	fd2;
	int	fd3;
	int	fd4;

	fd1 = 0;
	fd2 = 0;
	fd3 = 0;
	fd4 = 0;
	if (minis->exec->fd_pipe[PIPE_READ] != STDIN_FILENO)
		fd1 = dup_and_close_pipes(minis, PIPE_READ);
	if (minis->exec->fd_prev_out != STDOUT_FILENO)
		fd2 = dup_and_close_pipes(minis, PIPE_WRITE);
	if (minis->exec->fd_in != STDIN_FILENO)
		fd3 = dup_and_close_redir(minis, READ);
	if (minis->exec->fd_out != STDOUT_FILENO)
		fd4 = dup_and_close_pipes(minis, PIPE_WRITE);
	if (minis->exec->fd_pipe[PIPE_WRITE] != STDOUT_FILENO)
		close_unused(minis, PIPE_WRITE);
	check_fd(fd1, fd2, fd3, fd4);
}

void	dup_and_close(t_minist *minis, t_cmd childno)
{
	if (childno == CMD_FIRST)
		manage_child_first(minis);
	else if (childno == CMD_LAST)
		manage_child_last(minis);
	else
		manage_child_inter(minis);
}

void	child_error(t_minist *minis, t_parser *parser_ptr)
{
	int		code;

	if (minis->err->code != NO_ERR)
	{
		code = minis->exit_code;
		free_minist();
		free(minis);
		exit(code);
	}
	if (!parser_ptr->value && check_for_fork(parser_ptr))
	{
		free_minist();
		free(minis);
		exit(EXIT_FAILURE);
	}
}
