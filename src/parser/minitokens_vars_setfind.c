/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitokens_vars_setfind.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:02:13 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/14 03:19:19 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*find_var(t_minist *minis, char *word, int name_count)
{
	t_list	*var_ptr;
	int		var_name;

	var_ptr = minis->env_list;
	if (!minis->env_list || minis->env_list == NULL)
		return (NULL);
	var_name = check_var(var_ptr->content);
	while (var_ptr && !(var_name == name_count
			&& ft_strncmp(&(word[minis->token_i])
				, var_ptr->content, var_name) == 0))
	{
		var_ptr = var_ptr->next;
		if (var_ptr != NULL)
			var_name = check_var(var_ptr->content);
	}
	if (var_ptr == NULL)
		return (NULL);
	return (var_ptr);
}

char	*set_tmp_var(t_minist *minis, char *word, char *tmp)
{
	char	*var;
	char	*tmp_var;

	var = NULL;
	if (word && word[minis->token_i] && word[minis->token_i] == '$')
		var = var_no_quotes(minis, word);
	else
		var = ft_strdup("");
	tmp_var = ft_strjoin(tmp, var);
	if (var)
		free(var);
	free(tmp);
	if (!tmp_var)
		return (set_error(minis->err, ERR_ALLOC, "set_tmp_var"), NULL);
	return (tmp_var);
}

bool	set_res(t_minist *minis, char **res, char **tmp_var)
{
	char	*tmp;

	if (*tmp_var != NULL && *res != NULL)
	{
		tmp = ft_strjoin(*res, *tmp_var);
		free(*tmp_var);
		free (*res);
		if (!tmp)
			return (set_error(minis->err, ERR_ALLOC, "set_res:tmp"), false);
		*res = ft_strdup(tmp);
	}
	else if (*tmp_var != NULL)
	{
		*res = ft_strdup(*tmp_var);
		free(*tmp_var);
		if (!*res)
			return (set_error(minis->err, ERR_ALLOC, "set_res:res"), false);
	}
	return (true);
}

int	check_var(char *word)
{
	int		i;

	i = 0;
	while ((ft_isalnum(word[i]) || word[i] == '=' || word[i] == '_'
			|| word[i] == '?'))
	{
		if (word[i] == '=')
			return (i);
		i++;
	}
	return (0);
}
