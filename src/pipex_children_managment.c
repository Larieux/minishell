/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children_managment.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:21:02 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/06 10:58:17 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	lst_pid(t_minist *s_minis, pid_t pid)
{
	t_list	*new_pid_lst;

	new_pid_lst = ft_lstnew(pid);
	if (new_pid_lst == NULL)
	{
		write(2, "list malloc error\n", 19);
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(&(s_minis->pid_lst), new_pid_lst);
}

void	dup_and_close(int fd, int *fd_pipe, int fd_prev_out, int childno)
{
	if (childno == 0)
	{
		dup2(fd_pipe[READ], STDIN_FILENO);
		close(fd_pipe[READ]);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		close(fd_pipe[WRITE]);
	}
	else if (childno == 2)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(fd_pipe[WRITE], STDOUT_FILENO);
		close(fd_pipe[WRITE]);
		close(fd_pipe[READ]);
	}
	else
	{
		dup2(fd_pipe[READ], STDIN_FILENO);
		close(fd_pipe[READ]);
		dup2(fd_prev_out, STDOUT_FILENO);
		close(fd_prev_out);
		close(fd_pipe[WRITE]);
	}
}

void	execve_error(t_minist *s_minis, char **dtab, char **dtab2, char *tab)
{
	int		errorlen;
	char	*build_error;
	char	*build_error2;
	char	*error;

	if (dtab[1])
	{
		build_error = ft_strjoin(dtab[0], " ");
		build_error2 = ft_strjoin(build_error, dtab[1]);
		error = ft_strjoin(build_error2, " not found\n");
		free(build_error);
		free(build_error2);
	}
	else
		error = ft_strjoin(dtab[0], " not found\n");
	errorlen = ft_strlen(error);
	write(2, error, errorlen);
	free(error);
	free_dtab(dtab);
	free(dtab2);
	free(tab);
	ft_lstclear(&(s_minis->pid_lst));
	exit(EXIT_FAILURE);
}
