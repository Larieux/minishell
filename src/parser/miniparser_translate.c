/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniparser_translate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:02:57 by mlarieux          #+#    #+#             */
/*   Updated: 2025/03/11 13:02:58 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command(t_minist *minis, t_parser **parser
		, t_tokens **tokens)
{
	int	i;
	int	len;

	len = get_cmd_len(*tokens);
	add_node(minis, parser, 0);
	if (!(*parser))
		return ;
	(*parser)->value = ft_strdup((*tokens)->data);
	if (!(*parser)->value)
		return (set_error(minis->err, ERR_ALLOC, "handle_cmd_1"), (void )0);
	(*parser)->exp_value = malloc(sizeof(char *) * (len + 1));
	if (!(*parser)->exp_value)
		return (set_error(minis->err, ERR_ALLOC, "handle_cmd_2"), (void )0);
	ft_memset((*parser)->exp_value, 0, sizeof(char *) * (len + 1));
	i = 0;
	while (*tokens && i < len)
	{
		(*parser)->exp_value[i++] = ft_strdup((*tokens)->data);
		(*tokens) = (*tokens)->next;
	}
}

void	handle_redir(t_minist *minis, t_parser **parser, t_tokens **tokens)
{
	t_inout		*io_ptr;

	add_node(minis, parser, 0);
	if (!(*parser))
		return ;
	io_ptr = (*parser)->io;
	while (io_ptr && io_ptr->next)
		io_ptr = io_ptr->next;
	add_io_node(minis, parser, &io_ptr);
	ft_memset(io_ptr, 0, sizeof(t_inout));
	if ((*tokens)->type_data == T_REDIR_IN)
		io_ptr->type = IO_IN;
	else if ((*tokens)->type_data == T_REDIR_HDOC)
		io_ptr->type = IO_HEREDOC;
	else if ((*tokens)->type_data == T_REDIR_OUT)
		io_ptr->type = IO_OUT;
	else if ((*tokens)->type_data == T_REDIR_OUT_APP)
		io_ptr->type = IO_APPEND;
	if (!(*tokens)->next)
		return (set_error(minis->err, ERR_SYNTAX,
				token_name((*tokens)->type_data)), (void )0);
	(*tokens) = (*tokens)->next;
	io_ptr->value = ft_strdup((*tokens)->data);
	if (io_ptr->type == IO_IN)
		(*parser)->redir_in = true;
}

void	handle_pipe(t_minist *minis, t_parser **parser)
{
	if (!(*parser) || (*parser)->pipe == true)
		return (set_error(minis->err, ERR_SYNTAX, "|"),
			(void )0);
	add_node(minis, parser, 1);
	if (!(*parser))
		return (set_error(minis->err, ERR_ALLOC, "handle_pipe"), (void )0);
}

void	handle_parser(t_minist *minis, t_tokens **token_ptr,
		t_parser **parser_ptr)
{
	if (*token_ptr && ((*token_ptr)->type_data == T_WORD
			|| (*token_ptr)->type_data == T_VAR))
		handle_command(minis, parser_ptr, token_ptr);
	if (*token_ptr && (*token_ptr)->type_data >= T_REDIR_IN
		&& (*token_ptr)->type_data <= T_REDIR_OUT_APP)
		handle_redir(minis, parser_ptr, token_ptr);
	if (*token_ptr && (*token_ptr)->type_data == T_PIPE)
		handle_pipe(minis, parser_ptr);
	if (*token_ptr)
		*token_ptr = (*token_ptr)->next;
}

void	translate_tokens(t_minist *minis)
{
	t_tokens	*token_ptr;
	t_parser	*parser_ptr;

	token_ptr = minis->tokens;
	parser_ptr = minis->parser;
	while (token_ptr && minis->err->code == NO_ERR)
		handle_parser(minis, &token_ptr, &parser_ptr);
	while (parser_ptr && parser_ptr->left)
		parser_ptr = parser_ptr->left;
	if (parser_ptr)
		minis->parser = parser_ptr;
}
