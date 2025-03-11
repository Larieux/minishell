/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitokens_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:54:05 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 13:24:55 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_s_quotes(t_minist *minis, char **word)
{
	if (minis->token_end > minis->token_i && *word
		&& (*word)[minis->token_i] && (*word)[minis->token_i] != '\'')
	{
		minis->token_i++;
		handle_word(minis, L_IN_SQUOTE, word);
	}
}

void	handle_d_quotes(t_minist *minis, char **word)
{
	if (minis->token_end > minis->token_i && *word
		&& (*word)[minis->token_i] && (*word)[minis->token_i] == '$')
	{
		var_quotes(minis, word);
	}
	if (minis->token_end > minis->token_i && *word
		&& (*word)[minis->token_i] && (*word)[minis->token_i] != '\"'
			&& &((*word)[minis->token_end]) > &((*word)[minis->token_i]))
	{
		if ((*word)[minis->token_i] != '$')
			minis->token_i++;
		handle_word(minis, L_IN_DQUOTE, word);
	}
}

void	handle_word_default(t_minist *minis, t_lexstate state, char **word)
{
	if (minis->token_end > minis->token_i && state == L_DEFAULT && *word
		&& (*word)[minis->token_i] && (*word)[minis->token_i] != '<'
		&& (*word)[minis->token_i] != '>' && (*word)[minis->token_i] != '|'
		&& (*word)[minis->token_i] != ' ' && (*word)[minis->token_i] != '	'
		&& (*word)[minis->token_i] != '\n')
	{
		if ((*word)[minis->token_i] != '$' && (*word)[minis->token_i] != '\''
		&& (*word)[minis->token_i] != '\"')
			minis->token_i++;
		handle_word(minis, L_DEFAULT, word);
	}
}

void	handle_word(t_minist *minis, t_lexstate state, char **word)
{
	if (state == L_DEFAULT)
	{
		if (minis->token_end > minis->token_i && *word
			&& (*word)[minis->token_i] && (*word)[minis->token_i] == '$')
		{
			var_quotes(minis, word);
		}
		if (minis->token_end > minis->token_i && *word
			&& (*word)[minis->token_i] && (*word)[minis->token_i] == '\'')
			handle_quotes(minis, word, QUOTES_S);
		if (minis->token_end > minis->token_i && *word
			&& (*word)[minis->token_i] && (*word)[minis->token_i] == '\"')
			handle_quotes(minis, word, QUOTES_D);
		handle_word_default(minis, state, word);
	}
	if (state == L_IN_SQUOTE)
		handle_s_quotes(minis, word);
	else if (state == L_IN_DQUOTE)
		handle_d_quotes(minis, word);
}

void	continue_data(t_minist *minis, t_tokens *token_ptr, char **word)
{
	minis->token_end = 0;
	while (*word && (*word)[minis->token_end])
		minis->token_end++;
	if (minis->token_end > minis->token_i && *word && (*word)[minis->token_i]
		&& ((token_ptr->type_data == T_WORD
			|| token_ptr->type_data == T_D_QUOTE
			|| token_ptr->type_data == T_S_QUOTE)
		&& (*word)[minis->token_i] != '<'
		&& (*word)[minis->token_i] != '>' && (*word)[minis->token_i] != '|'
		&& (*word)[minis->token_i] != ' ' && (*word)[minis->token_i] != '	'
		&& (*word)[minis->token_i] != '\n'))
	{
		check_tokens(minis, &(token_ptr->type_data), *word, &(minis->token_i));
		if (minis->token_end > minis->token_i)
			set_word_data(minis, token_ptr, word);
	}
}
