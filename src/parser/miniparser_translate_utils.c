/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniparser_translate_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:02:49 by mlarieux          #+#    #+#             */
/*   Updated: 2025/03/11 13:02:51 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*new_parser_node(int reset)
{
	t_minist	*minis;
	t_parser	*node;
	static int	cmd_num = 0;

	minis = get_minist();
	node = malloc(sizeof(t_parser));
	if (!node)
		return (set_error(minis->err, ERR_ALLOC, "new_parser_node"), NULL);
	ft_memset(node, 0, sizeof(t_parser));
	if (reset == 1)
		cmd_num = 0;
	node->cmd_num = ++cmd_num;
	return (node);
}

void	add_node(t_minist *minis, t_parser **parser, int role)
{
	t_parser	*node;

	if (!(*parser) || (role == 1 && (*parser)->pipe == false))
	{
		node = new_parser_node(*parser == NULL);
		if (!node)
			return (set_error(minis->err, ERR_ALLOC, "add_node")
				, (void)0);
		if (*parser)
		{
			(*parser)->right = node;
			node->left = *parser;
		}
		*parser = node;
	}
	if (role == 0)
		(*parser)->pipe = false;
	else if (role == 1)
		(*parser)->pipe = true;
}

bool	add_io_node(t_minist *minis, t_parser **parser, t_inout **io_ptr)
{
	if (*io_ptr)
	{
		(*io_ptr)->next = malloc(sizeof(t_inout));
		if (!(*io_ptr)->next)
			return (set_error(minis->err, ERR_ALLOC, "add_io_node 1"), false);
		*io_ptr = (*io_ptr)->next;
	}
	else
	{
		*io_ptr = malloc(sizeof(t_inout));
		if (!(*io_ptr))
			return (set_error(minis->err, ERR_ALLOC, "add_io_node 2"), false);
		(*parser)->io = *io_ptr;
	}
	return (true);
}

int	get_cmd_len(t_tokens *tokens)
{
	int			i;
	t_tokens	*t;

	i = 0;
	t = tokens;
	while (t)
	{
		if (t->type_data == T_WORD || t->type_data == T_D_QUOTE
			|| t->type_data == T_S_QUOTE || t->type_data == T_VAR)
			i++;
		else
			break ;
		t = t->next;
	}
	return (i);
}

void	translate_error(t_minist *minis, t_tokens *token_ptr)
{
	token_ptr = minis->tokens;
	while (token_ptr->next)
		token_ptr = token_ptr->next;
	set_error(minis->err, ERR_SYNTAX, token_ptr->data);
	return (show_error(minis->err), (void )0);
}
