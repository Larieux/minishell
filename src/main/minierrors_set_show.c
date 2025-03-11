/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minierrors_set_show.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:30:28 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 11:34:30 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	show_error(t_error *err)
{
	ft_putstr_fd(P_AQUA"minishell: "P_ORANGE, 2);
	if (!err->msg)
		ft_putstr_fd(get_error(err->code), 2);
	else
	{
		if (err->code == ERR_CMD)
			(ft_putstr_fd(err->msg, 2), ft_putstr_fd(" ", 2));
		else if (err->code != ERR_UNKNOWN)
			ft_putstr_fd(get_error(err->code), 2);
		else
			ft_putstr_fd(err->msg, 2);
		if (err->code == ERR_HEREDOC)
		{
			ft_putstr_fd(err->msg, 2);
			ft_putstr_fd("')", 2);
		}
		else if (err->code == ERR_SYNTAX)
		{
			ft_putstr_fd(" `", 2);
			ft_putstr_fd(err->msg, 2);
			ft_putstr_fd("'", 2);
		}
	}
	ft_putstr_fd(RESET"\n", 2);
	return (false);
}

int	set_error(t_error *err, t_error_type type, char *s)
{
	int	code;

	code = 1;
	if (errno > 0)
	{
		code = errno_to_code(errno);
		err->code = ERR_UNKNOWN;
		err->msg = strerror(errno);
	}
	else
	{
		if (type == ERR_FD)
			code = 2;
		if (type == ERR_SYNTAX)
			code = 2;
		if (type == ERR_CMD)
			code = 127;
		if (type == ERR_ACCESS)
			code = 126;
		err->code = type;
		err->msg = s;
	}
	if (get_minist())
		get_minist()->exit_code = code;
	return (code);
}

bool	set_show_error(t_error *err, t_error_type type, char *s)
{
	set_error(err, type, s);
	show_error(err);
	return (false);
}
