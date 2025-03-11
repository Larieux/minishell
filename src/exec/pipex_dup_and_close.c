/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_dup_and_close.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:35:23 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/14 06:34:27 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_and_close_pipes(t_minist *minis, int role)
{
	int	fd;

	fd = 0;
	if (role == PIPE_READ)
	{
		if (minis->exec->fd_pipe[PIPE_READ] == -1)
			return (-1);
		fd = dup2(minis->exec->fd_pipe[PIPE_READ], STDIN_FILENO);
		close(minis->exec->fd_pipe[PIPE_READ]);
	}
	else if (role == PIPE_WRITE)
	{
		if (minis->exec->fd_prev_out == -1)
			return (-1);
		fd = dup2(minis->exec->fd_prev_out, STDOUT_FILENO);
		close(minis->exec->fd_prev_out);
	}
	return (fd);
}

int	dup_and_close_redir(t_minist *minis, int role)
{
	int	fd;

	fd = 0;
	if (role == READ)
	{
		if (minis->exec->fd_in == -1)
			return (-1);
		fd = dup2(minis->exec->fd_in, STDIN_FILENO);
		close(minis->exec->fd_in);
	}
	else if (role == WRITE)
	{
		if (minis->exec->fd_out == -1)
			return (-1);
		fd = dup2(minis->exec->fd_out, STDOUT_FILENO);
		close(minis->exec->fd_out);
	}
	return (fd);
}
