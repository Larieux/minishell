/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:59:01 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/06 10:58:15 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	wait_each_pid(t_minist *s_minis)
{
	t_list	*lst;
	int		status;

	lst = s_minis->pid_lst;
	waitpid(lst->content, &status, 0);
	lst = lst->next;
	while (lst)
	{
		waitpid(lst->content, NULL, 0);
		lst = lst->next;
	}
	return (status);
}

void	do_fork(t_minist *s_minis, int *fd_pipe, int fd_prev_out, int role)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (role == 0)
			child(s_minis, fd_pipe);
		else if (role == 2)
			child2(s_minis, fd_pipe, fd_prev_out);
		else
			inter_child(s_minis, fd_pipe, fd_prev_out);
	}
	else
	{
		if (role == 0 || role == 1)
			close(fd_pipe[0]);
		if (role == 1 || role == 2)
			close(fd_prev_out);
		lst_pid(s_minis, pid);
	}
}

void	do_pipe(int *fd_pipe)
{
	if (pipe(fd_pipe) == -1)
	{
		write(2, "pipe error\n", 12);
		exit(EXIT_FAILURE);
	}
}

void	do_pipex(t_minist *s_minis, int argc)
{
	int	fd_pipe[2];
	int	fd_prev_out;

	while (s_minis->arg_c >= s_minis->first_cmd)
	{
		if (s_minis->arg_c == s_minis->first_cmd)
			do_fork(s_minis, fd_pipe, fd_prev_out, 2);
		else if (s_minis->arg_c == argc - 2)
		{
			do_pipe(fd_pipe);
			do_fork(s_minis, fd_pipe, -1, 0);
			fd_prev_out = fd_pipe[1];
		}
		else
		{
			do_pipe(fd_pipe);
			do_fork(s_minis, fd_pipe, fd_prev_out, 1);
			fd_prev_out = fd_pipe[1];
		}
		s_minis->arg_c--;
	}
}
