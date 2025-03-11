/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:39:43 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 17:47:15 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_var_cwd(t_minist *minis, char **var, char **var_val)
{
	*var_val = getcwd(NULL, 0);
	var[0] = ft_strjoin("PWD=", *var_val);
	if (!var[0])
		return (free(*var_val), free(var)
			, set_error(minis->err, ERR_ALLOC, "lexer_3"), (void )0);
	ft_export(minis, &(var[0]));
	free(*var_val);
	free(var[0]);
}

void	set_vars(t_minist *minis)
{
	char	**var;
	char	*var_val;

	var_val = ft_itoa(minis->exit_code);
	if (!var_val)
		return (set_error(minis->err, ERR_ALLOC, "lexer_1"), (void )0);
	var = malloc(2 * sizeof(char *));
	if (!var)
		return (free(var_val)
			, set_error(minis->err, ERR_ALLOC, "lexer_3"), (void )0);
	var[1] = NULL;
	var[0] = ft_strjoin("?=", var_val);
	if (!var[0])
		return (free(var_val), free(var)
			, set_error(minis->err, ERR_ALLOC, "lexer_3"), (void )0);
	ft_export(minis, &(var[0]));
	free(var_val);
	free(var[0]);
	set_var_cwd(minis, var, &var_val);
	free(var);
}

void	lexer(t_minist *minis)
{
	set_vars(minis);
	set_tokens(minis);
	if (minis->err->code == NO_ERR)
		translate_tokens(minis);
	free_tokens(&(minis->tokens));
}

bool	parser(t_minist *minis)
{
	int		i;

	i = 0;
	minis->err->code = NO_ERR;
	minis->state = READLINE;
	minis->line = readline ("minishell$ ");
	if (!minis->line)
		return (ft_ctrl_d(minis));
	while (minis->line && minis->line[i] == ' ')
		i++;
	if (minis->line && *(minis->line) && *(minis->line) != '\n')
	{
		add_history(minis->line);
		lexer(minis);
		if (minis->err->code != NO_ERR)
		{
			show_error(minis->err);
		}
	}
	return (true);
}
