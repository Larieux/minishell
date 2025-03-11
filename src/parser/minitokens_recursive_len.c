/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitokens_recursive_len.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:10:19 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/15 15:27:32 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	continue_len(t_minist *minis, t_tokens *token_ptr, int *k)
{
	if ((token_ptr->type_len == T_S_QUOTE
			&& minis->line[minis->token_end] == '\'')
		|| (token_ptr->type_len == T_D_QUOTE
			&& minis->line[minis->token_end] == '\"'))
	{
		*k += 1;
		minis->token_end++;
	}
	check_tokens(minis, &(token_ptr->type_len), minis->line, k);
	if (token_ptr->type_len == T_D_QUOTE
		|| token_ptr->type_len == T_S_QUOTE
		|| token_ptr->type_len == T_WORD
		|| token_ptr->type_len == T_VAR)
	{
		*k += 1;
		minis->token_end++;
		if (((token_ptr->type_len == T_D_QUOTE
					&& minis->line[minis->token_end] == '\"')
				|| (token_ptr->type_len == T_S_QUOTE
					&& minis->line[minis->token_end] == '\'')))
			continue_len(minis, token_ptr, k);
		set_token_end(minis, token_ptr);
	}
	if (minis->token_end > *k && token_ptr->type_len != T_END)
		rec_len(minis, token_ptr, k);
}

void	check_continue_len(t_minist *minis, t_tokens *token_ptr, int *k)
{
	if (token_ptr->type_len != T_END && minis->line[*k]
		&& ((token_ptr->type_data == T_WORD
				|| token_ptr->type_data == T_D_QUOTE
				|| token_ptr->type_data == T_S_QUOTE
				|| token_ptr->type_data == T_VAR)
			&& minis->line[*k] != '|'
			&& minis->line[*k] != '<' && minis->line[*k] != '>'
			&& minis->line[*k] != ' ' && minis->line[*k] != '	'
			&& minis->line[*k] != '\n'))
		continue_len(minis, token_ptr, k);
}

void	rec_len(t_minist *minis, t_tokens *token_ptr, int *k)
{
	if (token_ptr->type_len != T_END
		&& minis->token_end > *k && minis->line && minis->line[*k]
		&& token_ptr->type_len == T_VAR && (ft_isalnum(minis->line[*k])
			|| minis->line[*k] == '_' || minis->line[*k] == '$'
			|| minis->line[*k] == '?'))
		token_len(minis, token_ptr, k);
	set_token_len_quotes(minis, token_ptr, k);
	set_token_len_word(minis, token_ptr, k);
	check_continue_len(minis, token_ptr, k);
}
