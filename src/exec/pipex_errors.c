/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:30:23 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 13:57:59 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_error(t_minist *minis, char *str)
{
	if (errno == ENOENT)
	{
		set_error(minis->err, ERR_NOT_EXIST, str);
		minis->exit_code = 2;
	}
	else if (errno == EACCES)
	{
		set_error(minis->err, ERR_ACCESS, str);
		minis->exit_code = 1;
	}
	else
		set_error(minis->err, ERR_SYNTAX, str);
}

void	mini_execve_error(char **dtab, char **dtab2, char *tabb)
{
	t_minist	*minis;
	int			code;

	minis = get_minist();
	if (dtab && dtab[0])
		set_error(minis->err, ERR_CMD, dtab[0]);
	if (minis->err)
		show_error(minis->err);
	free_dtab(dtab);
	free(dtab2);
	free(tabb);
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
