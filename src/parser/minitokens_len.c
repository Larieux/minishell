/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitokens_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:25:47 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/15 15:27:54 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token_end(t_minist *minis, t_tokens *token_ptr)
{
	while (token_ptr->type_len != T_END
		&& minis->line[minis->token_end]
		&& (((token_ptr->type_len == T_WORD
					|| token_ptr->type_len == T_VAR)
				&& (minis->line[minis->token_end] != '<'
					&& minis->line[minis->token_end] != '>'
					&& minis->line[minis->token_end] != '|'
					&& minis->line[minis->token_end] != '\n'
					&& minis->line[minis->token_end] != '\"'
					&& minis->line[minis->token_end] != '\''
					&& minis->line[minis->token_end] != ' '
					&& minis->line[minis->token_end] != '	'))
			|| ((token_ptr->type_len == T_S_QUOTE
					&& minis->line[minis->token_end] != '\'')
				|| (token_ptr->type_len == T_D_QUOTE
					&& minis->line[minis->token_end] != '\"'))))
		minis->token_end++;
}

void	token_len(t_minist *minis, t_tokens *token_ptr, int *k)
{
	if (minis->token_end > *k)
	{
		*k += 1;
		if (minis->token_end > *k)
			rec_len(minis, token_ptr, k);
	}
}

void	set_token_len_word(t_minist *minis, t_tokens *token_ptr
		, int *k)
{
	if (token_ptr->type_len == T_END)
		return ;
	if (minis->token_end > *k && minis->line && minis->line[*k]
		&& ((token_ptr->type_len == T_WORD && minis->line[*k] != '<'
				&& minis->line[*k] != '>' && minis->line[*k] != '|'
				&& minis->line[*k] != ' ' && minis->line[*k] != '	')))
	{
		if (minis->line[*k] == '\"')
		{
			token_ptr->type_len = T_D_QUOTE;
			token_len(minis, token_ptr, k);
			token_ptr->type_len = T_WORD;
		}
		if (minis->line[*k] == '\'')
		{
			token_ptr->type_len = T_S_QUOTE;
			token_len(minis, token_ptr, k);
			token_ptr->type_len = T_WORD;
		}
		token_len(minis, token_ptr, k);
	}
}

void	set_token_len_quotes(t_minist *minis, t_tokens *token_ptr
		, int *k)
{
	if (token_ptr->type_len == T_END)
		return ;
	if (minis->token_end > *k && minis->line && minis->line[*k]
		&& (token_ptr->type_len == T_S_QUOTE && minis->line[*k] != '\''))
	{
		token_len(minis, token_ptr, k);
	}
	if (minis->token_end >= *k && minis->line && minis->line[*k]
		&& (token_ptr->type_len == T_D_QUOTE && minis->line[*k] != '\"'))
	{
		token_len(minis, token_ptr, k);
	}
}

void	set_token_len(t_minist *minis, t_tokens *token_ptr, int *k)
{
	minis->token_end = *k;
	set_token_end(minis, token_ptr);
	if ((token_ptr->type_len == T_REDIR_IN && minis->line[*k] == '<')
		|| (token_ptr->type_len == T_REDIR_OUT && minis->line[*k] == '>'))
	{
		*k += 1;
		minis->token_end = *k;
	}
	else if ((token_ptr->type_len == T_REDIR_HDOC
			&& minis->line[*k] == '<' && minis->line[*k + 1] == '<')
		|| (token_ptr->type_len == T_REDIR_OUT_APP
			&& minis->line[*k] == '>' && minis->line[*k + 1] == '>'))
	{
		*k += 2;
		minis->token_end = *k;
	}
	else if (minis->line && minis->line[*k]
		&& token_ptr->type_len == T_PIPE && minis->line[*k] == '|')
	{
		*k += 1;
		minis->token_end = *k;
	}
	else
		rec_len(minis, token_ptr, k);
}
