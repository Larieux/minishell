/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children_utilities.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:13:07 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 14:25:13 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_out(char *str, int role)
{
	int	fd;

	if (!(ft_strncmp(str, "/dev/stdout", 12) == 0 && ft_strlen(str) == 11))
	{
		if (role == 1)
			fd = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			fd = open(str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		return (fd);
	}
	return (STDOUT_FILENO);
}

void	open_io(t_minist *minis, t_inout *io_ptr, int role)
{
	if (role == 0)
	{
		if (minis->exec->fd_in != STDIN_FILENO && minis->exec->fd_in != -1)
			close(minis->exec->fd_in);
		if (io_ptr->type == IO_HEREDOC)
			minis->exec->fd_in = open("/tmp/tmp_heredoc", O_RDONLY, 0644);
		else
			minis->exec->fd_in = open(io_ptr->value, O_RDONLY, 0644);
	}
	else if (role == 1)
	{
		if (minis->exec->fd_out != STDOUT_FILENO && minis->exec->fd_out != -1)
			close(minis->exec->fd_out);
		minis->exec->fd_out = open_out(io_ptr->value, 1);
	}
	else if (role == 2)
	{
		if (minis->exec->fd_out != STDOUT_FILENO && minis->exec->fd_out != -1)
			close(minis->exec->fd_out);
		minis->exec->fd_out = open_out(io_ptr->value, 2);
	}
}

void	check_for_io(t_minist *minis, t_parser *parser_ptr)
{
	t_inout	*io_ptr;

	io_ptr = parser_ptr->io;
	while (io_ptr != NULL)
	{
		if ((io_ptr->type == IO_IN
				|| io_ptr->type == IO_HEREDOC)
			&& check_built_ins(minis, parser_ptr, B_I_CHECK) == false)
			open_io(minis, io_ptr, 0);
		else if (io_ptr->type == IO_OUT)
			open_io(minis, io_ptr, 1);
		else if (io_ptr->type == IO_APPEND)
			open_io(minis, io_ptr, 2);
		if (minis->exec->fd_in == -1 || minis->exec->fd_out == -1)
		{
			if (minis->exec->fd_in != -1 && minis->exec->fd_in != STDIN_FILENO)
				close (minis->exec->fd_in);
			if (minis->exec->fd_out != -1
				&& minis->exec->fd_out != STDOUT_FILENO)
				close (minis->exec->fd_out);
			fd_error(minis, io_ptr->value);
		}
		io_ptr = io_ptr->next;
	}
}

void	close_unused(t_minist *minis, int role)
{
	if (role == PIPE_READ)
	{
		if (minis->exec->fd_pipe[PIPE_READ] == -1)
			return ;
		close(minis->exec->fd_pipe[PIPE_READ]);
		minis->exec->fd_pipe[PIPE_READ] = STDIN_FILENO;
	}
	else if (role == PIPE_WRITE)
	{
		if (minis->exec->fd_pipe[PIPE_WRITE] == -1)
			return ;
		close(minis->exec->fd_pipe[PIPE_WRITE]);
		minis->exec->fd_pipe[PIPE_WRITE] = STDOUT_FILENO;
	}
}

void	check_fd(int fd1, int fd2, int fd3, int fd4)
{
	t_minist	*minis;
	int			code;

	if (fd1 == -1 || fd2 == -1 || fd3 == -1 || fd4 == -1)
	{
		minis = get_minist();
		if (minis->exec->fd_in != -1 && minis->exec->fd_in != STDIN_FILENO)
			close (minis->exec->fd_in);
		if (minis->exec->fd_out != -1 && minis->exec->fd_out != STDOUT_FILENO)
			close (minis->exec->fd_out);
		fd_error(minis, "fd");
		if (minis->err)
			show_error(minis->err);
		if (minis->exit_code > 0)
		{
			code = minis->exit_code;
			free_minist();
			free(minis);
			exit(code);
		}
		free_minist();
		free(minis);
		exit(EXIT_FAILURE);
	}
}
