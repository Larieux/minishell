/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:59:35 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/15 15:28:11 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_redirs(t_minist *minis, t_token_type *type, char *word, int i)
{
	if (word[i] == '<')
	{
		if (word[i + 1] == '<')
			*type = T_REDIR_HDOC;
		else
			*type = T_REDIR_IN;
		if (word[i + 1] && word[i + 2]
			&& (word[i + 2] == '<' || word[i + 2] == '>'))
			return (set_error(minis->err, ERR_SYNTAX, "`<'"), false);
		return (true);
	}
	else if (word[i] == '>')
	{
		if (word[i + 1] == '>')
			*type = T_REDIR_OUT_APP;
		else
			*type = T_REDIR_OUT;
		if (word[i + 2] == '<' || word[i + 2] == '>')
			return (set_error(minis->err, ERR_SYNTAX, "`>'"), false);
		return (true);
	}
	return (false);
}

void	check_tokens(t_minist *minis, t_token_type *type, char *word, int *i)
{
	if (!word || !(word[*i]))
	{
		*type = T_END;
		return ;
	}
	else if (check_redirs(minis, type, word, *i))
		return ;
	else if (word[*i] == '|')
		*type = T_PIPE;
	else if (word[*i] == '\"')
		*type = T_D_QUOTE;
	else if (word[*i] == '\'')
		*type = T_S_QUOTE;
	else if (*type != T_S_QUOTE && word[*i] == '$')
		*type = T_VAR;
	else if (word[*i] == ' ' || word[*i] == '	')
		*type = T_END;
	else if (word[*i] != '<' && word[*i] != '>' && word[*i] != '|'
		&& word[*i] != '\'' && word[*i] != '\"' && word[*i] != '$'
		&& word[*i] != ' ' && word[*i] != '	' && word[*i] != '\n')
		*type = T_WORD;
	else
		set_error(minis->err, ERR_SYNTAX, token_name(*type));
}

void	set_word_data(t_minist *minis, t_tokens *token_ptr, char **word)
{
	minis->token_end = 0;
	while ((*word)[minis->token_end])
		minis->token_end++;
	if (token_ptr->type_data == T_WORD || token_ptr->type_data == T_VAR)
		handle_word(minis, L_DEFAULT, word);
	if (token_ptr->type_data == T_S_QUOTE)
	{
		rm_f_quote(minis, word, minis->token_i, QUOTES_S);
		handle_word(minis, L_IN_SQUOTE, word);
		rm_l_quote(minis, word, minis->token_i, QUOTES_S);
	}
	if (token_ptr->type_data == T_D_QUOTE)
	{
		rm_f_quote(minis, word, minis->token_i, QUOTES_D);
		handle_word(minis, L_IN_DQUOTE, word);
		rm_l_quote(minis, word, minis->token_i, QUOTES_D);
	}
	continue_data(minis, token_ptr, word);
}

char	*set_token_data(t_minist *minis, t_tokens *token_ptr, int *i)
{
	char	*word;
	char	*tmp;
	int		k;

	k = *i;
	if (token_ptr->type_len == T_VAR || token_ptr->type_len == T_D_QUOTE
		|| token_ptr->type_len == T_S_QUOTE)
		k++;
	set_token_len(minis, token_ptr, &k);
	if (!str_alloc(minis, &tmp, "set_tok_data_1"
			, (k - (*i) + 1) * sizeof(char)))
		return (NULL);
	ft_strlcpy(tmp, &(minis->line[*i]), k - (*i) + 1);
	minis->token_i = 0;
	set_word_data(minis, token_ptr, &tmp);
	word = ft_strdup(tmp);
	free(tmp);
	if (!word)
		return (set_error(minis->err, ERR_ALLOC, "set_tok_data_2"), NULL);
	if (token_ptr->type_data == T_D_QUOTE || token_ptr->type_data == T_S_QUOTE)
		token_ptr->type_data = T_WORD;
	*i = k;
	return (word);
}

void	set_tokens(t_minist *minis)
{
	t_tokens	*token_ptr;
	int			i;

	i = 0;
	minis->tokens = malloc (sizeof(t_tokens));
	if (!minis->tokens)
		set_error(minis->err, ERR_ALLOC, "set_tokens");
	token_ptr = minis->tokens;
	set_token_default(&token_ptr);
	while (token_ptr && minis->line && minis->line[i]
		&& minis->line[i] != '\n' && minis->err->code == NO_ERR)
	{
		set_token_default(&token_ptr);
		while (minis->line && minis->line[i]
			&& (minis->line[i] == ' ' || minis->line[i] == '	'))
			i++;
		check_tokens(minis, &token_ptr->type_len, minis->line, &i);
		check_tokens(minis, &token_ptr->type_data, minis->line, &i);
		token_ptr->data = set_token_data(minis, token_ptr, &i);
		check_var_space(minis, &token_ptr);
		while (minis->line && minis->line[i]
			&& (minis->line[i] == ' ' || minis->line[i] == '	'))
			i++;
		next_token(minis, &token_ptr, i, 0);
	}
}
