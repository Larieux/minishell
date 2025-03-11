/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitokens_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:21:17 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/17 12:41:57 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count(char *word, int i, int role)
{
	int	count;
	int	j;

	count = 0;
	j = i;
	if (role == 1 && *word == '?')
		return (1);
	while ((role == 0 && word[j]
			&& word[j] != '$' && word[j] != '\"' && word[j] != '\'')
		|| (role == 1 && word[j] && (ft_isalnum(word[j])
				|| word[j] == '_' || word[j] == '?')))
	{
		if (word[j] == '?')
			return (j);
		count++;
		j++;
	}
	return (count);
}

void	increment_two_int(int *k, int *len)
{
	*k += 1;
	*len += 1;
}

void	next_token(t_minist *minis, t_tokens **token_ptr, int i, int role)
{
	if ((role == 0 && minis->line && minis->line[i])
		|| role == 1)
	{
		(*token_ptr)->next = malloc (sizeof(t_tokens));
		if (!(*token_ptr)->next)
			set_error(minis->err, ERR_ALLOC, "next_token");
		else
			*token_ptr = (*token_ptr)->next;
		set_token_default(token_ptr);
	}
}

void	split_space(t_minist *minis, t_tokens **token_ptr, int i)
{
	char	**split;
	int		j;

	split = ft_split((*token_ptr)->data, ' ');
	if (!split)
		return (set_error(minis->err, ERR_ALLOC, "var_space_1"), (void )0);
	if (split && split[0])
	{
		free((*token_ptr)->data);
		(*token_ptr)->data = ft_strdup(split[0]);
		if (!(*token_ptr)->data)
			return (set_error(minis->err, ERR_ALLOC, "var_space_2"), (void )0);
	}
	j = 1;
	while (split && split[j])
	{
		next_token(minis, token_ptr, i, 1);
		(*token_ptr)->data = ft_strdup(split[j]);
		if (!(*token_ptr)->data)
			return (set_error(minis->err, ERR_ALLOC, "var_space_3"), (void )0);
		j++;
	}
	free_dtab(split);
}

void	check_var_space(t_minist *minis, t_tokens **token_ptr)
{
	int		i;

	i = 0;
	while ((*token_ptr) && (*token_ptr)->type_data
		&& (*token_ptr)->type_data == T_VAR
		&& (*token_ptr)->data && (*token_ptr)->data[i])
	{
		while ((*token_ptr) && (*token_ptr)->type_data
			&& (*token_ptr)->type_data == T_VAR
			&& (*token_ptr)->data && (*token_ptr)->data[i]
			&& (*token_ptr)->data[i] != ' ')
			i++;
		if ((*token_ptr) && (*token_ptr)->type_data
			&& (*token_ptr)->type_data == T_VAR
			&& (*token_ptr)->data && (*token_ptr)->data[i]
			&& (*token_ptr)->data[i] == ' ')
			split_space(minis, token_ptr, i);
	}
}
