/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniparser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:41:05 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/14 03:43:08 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token_default(t_tokens **token_ptr)
{
	(*token_ptr)->state = L_DEFAULT;
	(*token_ptr)->type_len = T_WORD;
	(*token_ptr)->type_data = T_WORD;
	(*token_ptr)->data = NULL;
	(*token_ptr)->next = NULL;
}

char	*token_type_name(t_token_type type)
{
	static char	*name[] = {
	[T_WORD] = "T_WORD",
	[T_VAR] = "T_VAR",
	[T_S_QUOTE] = "T_S_QUOTE",
	[T_D_QUOTE] = "T_D_QUOTE",
	[T_PIPE] = "T_PIPE",
	[T_REDIR_IN] = "T_REDIR_IN",
	[T_REDIR_OUT] = "T_REDIR_OUT",
	[T_REDIR_HDOC] = "T_REDIR_HDOC",
	[T_REDIR_OUT_APP] = "T_REDIR_OUT_APP"
	};

	if (type >= T_WORD && type <= T_REDIR_OUT_APP)
		return (name[type]);
	return ("");
}

char	*io_type_name(t_io_type type)
{
	static char	*name[] = {
	[IO_IN] = "IO_IN",
	[IO_OUT] = "IO_OUT",
	[IO_HEREDOC] = "IO_HEREDOC",
	[IO_APPEND] = "IO_APPEND",
	};

	if (type >= IO_IN && type <= IO_APPEND)
		return (name[type]);
	return ("");
}

void	ft_exit_failure(t_minist *minis)
{
	set_error(minis->err, ERR_ALLOC, "ft_exit_failure");
	show_error(minis->err);
	free_minist();
	free(minis);
	exit(EXIT_FAILURE);
}

bool	ft_ctrl_d(t_minist *minis)
{
	add_node(minis, &(minis->parser), 0);
	if (!minis->parser)
		ft_exit_failure(minis);
	minis->parser->exp_value = malloc(2 * sizeof(char *));
	if (!minis->parser->exp_value)
		ft_exit_failure(minis);
	minis->parser->exp_value[0] = ft_strdup("exit");
	if (!minis->parser->exp_value[0])
		ft_exit_failure(minis);
	minis->parser->exp_value[1] = NULL;
	return (ft_exit(minis, minis->parser->exp_value));
}
