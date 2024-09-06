/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:15:02 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/06 11:23:04 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pipex(t_minist *s_minis)
{
	int			status;

	if (errors(s_minis->arg_c_or, s_minis, s_minis->env) == -1)
		return (1);
	s_minis->arg_c = s_minis->arg_c_or - 2;
	s_minis->pid_lst = NULL;
	do_pipex(s_minis, s_minis->arg_c_or);
	status = wait_each_pid(s_minis);
	unlink ("/tmp/tmp_heredoc");
	ft_lstclear(&(s_minis->pid_lst));
	return (status);
}
