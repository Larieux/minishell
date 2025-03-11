/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitokens_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:53:48 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/17 12:38:36 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_no_quotes(t_minist *minis, char *word)
{
	t_list	*var_ptr;
	char	*res;
	int		name_count;

	res = NULL;
	minis->token_i++;
	if (!word[minis->token_i])
		return (res);
	name_count = ft_count(word, minis->token_i, 1);
	var_ptr = find_var(minis, word, name_count);
	minis->token_i += name_count;
	if (var_ptr == NULL)
		return (no_var(name_count));
	res = ft_strdup(&(((char *)var_ptr->content)[name_count + 1]));
	if (!res)
		return (set_error(minis->err, ERR_ALLOC, "var_no_quotes 4"), "ERROR");
	return (res);
}

void	count_not_zero(t_minist *minis, char **res)
{
	char	*tmp;
	char	*tmp_var;

	tmp = NULL;
	if (!str_alloc(minis, &tmp, "count_not_zero_1"
			, (minis->token_i + 1) * sizeof(char)))
		return ;
	ft_strlcpy(tmp, *res, minis->token_i + 1);
	tmp_var = set_tmp_var(minis, *res, tmp);
	if (!tmp_var)
		return ;
	free(*res);
	*res = ft_strdup(tmp_var);
	free(tmp_var);
	if (!res)
		return (set_error(minis->err, ERR_ALLOC, "count_not_zero_2"), (void)0);
}

void	count_zero(t_minist *minis, char **res)
{
	char	*tmp_var;

	tmp_var = var_no_quotes(minis, *res);
	if (!tmp_var)
		return ;
	free(*res);
	*res = ft_strdup(tmp_var);
	free(tmp_var);
	if (!res)
		return (set_error(minis->err, ERR_ALLOC, "count_zero_2"), (void)0);
}

void	after_var(t_minist *minis, char *before_var, char **res)
{
	char	*tmp;

	tmp = ft_strdup(*res);
	if (!tmp)
		return (set_error(minis->err, ERR_ALLOC, "after_var_1"), (void)0);
	free(*res);
	*res = ft_strjoin(tmp, &(before_var[minis->token_i]));
	minis->token_i = ft_strlen(tmp);
	free(tmp);
	if (!res || !(*res))
		return (set_error(minis->err, ERR_ALLOC, "after_var_2"), (void)0);
}

void	var_quotes(t_minist *minis, char **word)
{
	char	*res;
	char	*before_var;

	res = ft_strdup(*word);
	before_var = ft_strdup(res);
	if (minis->token_i > 0)
		count_not_zero(minis, &res);
	else
		count_zero(minis, &res);
	after_var(minis, before_var, &res);
	if (!res)
		return ;
	free(before_var);
	free(*word);
	*word = ft_strdup(res);
	minis->token_end = 0;
	while ((*word)[minis->token_end])
		minis->token_end++;
	free(res);
}
