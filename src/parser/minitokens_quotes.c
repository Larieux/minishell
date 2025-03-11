/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitokens_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:47:05 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/17 13:11:20 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	old_word_l(char **word, char *new_word, int i, int j)
{
	t_minist	*minis;
	char		*old_word;

	minis = get_minist();
	old_word = malloc((j + 1) * sizeof(char));
	if (!old_word)
		return (set_error(minis->err, ERR_ALLOC, "old_word_l_1"), (void)0);
	ft_strlcpy(old_word, &((*word)[i + 1]), j + 1);
	free(*word);
	*word = ft_strjoin(new_word, old_word);
	free(old_word);
	if (!(*word))
		return (set_error(minis->err, ERR_ALLOC, "old_word_l_2"), (void)0);
}

void	rm_l_quote(t_minist *minis, char **word, int i, t_quotes role)
{
	char	*new_word;
	int		j;

	j = i;
	if (!((*word)[i]) || ((role == QUOTES_S && (*word)[i] != '\'')))
		return (set_error(minis->err, ERR_NOQUOTE, "\'"), (void)0);
	if (!((*word)[i]) || (role == QUOTES_D && (*word)[i] != '\"'))
		return (set_error(minis->err, ERR_NOQUOTE, "\""), (void)0);
	new_word = malloc((j + 1) * sizeof(char));
	if (!new_word)
		return (set_error(minis->err, ERR_ALLOC, "rm_l_quote 1"), (void)0);
	ft_strlcpy(new_word, *word, j + 1);
	while ((*word)[j + 1])
		j++;
	if (&((*word)[j]) != &((*word)[i]))
		old_word_l(word, new_word, i, j);
	else
	{
		free(*word);
		*word = ft_strdup(new_word);
	}
	free(new_word);
	if (!(*word))
		return (set_error(minis->err, ERR_ALLOC, "rm_l_quote 2"), (void)0);
}

void	old_word_f(char **word, char *tmp, int i)
{
	t_minist	*minis;
	char		*old_word;

	minis = get_minist();
	old_word = malloc((i + 1) * sizeof(char));
	if (!old_word)
		return (set_error(minis->err, ERR_ALLOC, "old_word_f_1"), (void)0);
	ft_strlcpy(old_word, *word, i + 1);
	free(*word);
	*word = ft_strjoin(old_word, tmp);
	free(old_word);
	if (!(*word))
		return (set_error(minis->err, ERR_ALLOC, "old_word_f_2"), (void)0);
}

void	rm_f_quote(t_minist *minis, char **word, int i, t_quotes role)
{
	char	*tmp;

	if (!(*word))
		return (set_error(minis->err, ERR_ALLOC, "rm_f_quote 1"), (void)0);
	minis->token_end = 0;
	while ((*word)[minis->token_end])
		minis->token_end++;
	if (minis->token_end <= i || (role == QUOTES_S && (*word)[i] != '\'')
		|| (role == QUOTES_D && (*word)[i] != '\"'))
		return (set_error(minis->err, ERR_SYNTAX, "rm_f_quote 2"), (void)0);
	tmp = ft_strdup(&((*word)[i + 1]));
	if (!tmp)
		return (set_error(minis->err, ERR_ALLOC, "rm_f_quote 2"), (void)0);
	if (i != 0)
		old_word_f(word, tmp, i);
	else
	{
		free(*word);
		*word = ft_strdup(tmp);
	}
	free(tmp);
	if (!(*word))
		return (set_error(minis->err, ERR_ALLOC, "rm_f_quote 3"), (void)0);
}

void	handle_quotes(t_minist *minis, char **word, t_quotes role)
{
	minis->token_end = 0;
	while ((*word)[minis->token_end])
		minis->token_end++;
	if (role == QUOTES_S)
	{
		rm_f_quote(minis, word, minis->token_i, QUOTES_S);
		handle_word(minis, L_IN_SQUOTE, word);
		rm_l_quote(minis, word, minis->token_i, QUOTES_S);
	}
	else
	{
		rm_f_quote(minis, word, minis->token_i, QUOTES_D);
		handle_word(minis, L_IN_DQUOTE, word);
		rm_l_quote(minis, word, minis->token_i, QUOTES_D);
	}
	minis->token_end = 0;
	while ((*word)[minis->token_end])
		minis->token_end++;
}
