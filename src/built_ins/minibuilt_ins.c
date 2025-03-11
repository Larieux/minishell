/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibuilt_ins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:53:07 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 16:32:10 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	exec_built_ins(t_minist *minis, t_parser *parser_ptr, int which)
{
	signal(SIGPIPE, SIG_IGN);
	if (which == 0)
		ft_echo(parser_ptr->exp_value);
	else if (which == 1)
		ft_pwd();
	else if (which == 2)
		ft_env(minis);
	else if (which == 3)
		ft_export(minis, &(parser_ptr->exp_value[1]));
	else if (which == 4)
		ft_unset(minis, parser_ptr->exp_value, 1);
	else if (which == 5)
		ft_exit(minis, parser_ptr->exp_value);
	else if (which == 6)
		ft_cd(minis, parser_ptr);
	else
	{
		signal(SIGPIPE, SIG_DFL);
		set_vars(minis);
		return (false);
	}
	signal(SIGPIPE, SIG_DFL);
	set_vars(minis);
	return (true);
}

bool	check_for_fork(t_parser *parser_ptr)
{
	t_inout	*io_ptr;
	bool	res;

	io_ptr = parser_ptr->io;
	res = false;
	if (!io_ptr)
	{
		if (parser_ptr->right || parser_ptr->left)
			res = true;
	}
	while (io_ptr)
	{
		if (parser_ptr->right || parser_ptr->left
			|| (parser_ptr->io && parser_ptr->io->type
				&& (parser_ptr->io->type == IO_OUT
					|| parser_ptr->io->type == IO_APPEND)))
			res = true;
		io_ptr = io_ptr->next;
	}
	return (res);
}

void	ft_free_built_ins(t_parser *parser_ptr)
{
	t_minist	*minis;
	int			code;

	if (check_for_fork(parser_ptr) == true)
	{
		minis = get_minist();
		code = minis->exit_code;
		if (minis->err && minis->err->code != NO_ERR)
		{
			show_error(minis->err);
			free_minist();
			free(minis);
			exit(code);
		}
		free_minist();
		free(minis);
		exit(EXIT_SUCCESS);
	}
}

int	check_built_ins(t_minist *minis, t_parser *parser_ptr
	, t_check_built_in role)
{
	static const char	*built_ins[7] = {"echo", "pwd", "env", "export",
		"unset", "exit", "cd"};
	int					built_in_len;
	int					arg_len;
	int					i;

	i = 0;
	built_in_len = ft_strlen(built_ins[i]);
	arg_len = ft_strlen(parser_ptr->value);
	while (i < 7 && !(arg_len == built_in_len
			&& parser_ptr && parser_ptr->value
			&& ft_strncmp(parser_ptr->value,
				built_ins[i], built_in_len) == 0))
	{
		i++;
		built_in_len = ft_strlen(built_ins[i]);
	}
	if (role == B_I_CHECK && i == 6)
		return (true);
	if (role == B_I_CHECK && i < 6 && check_for_fork(parser_ptr) == false)
		return (true);
	if (role == B_I_EXECUTE && exec_built_ins(minis, parser_ptr, i) == true)
		return (ft_free_built_ins(parser_ptr), true);
	return (false);
}
