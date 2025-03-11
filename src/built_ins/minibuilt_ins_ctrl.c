/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibuilt_ins_ctrl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:21:11 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 17:26:48 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_minist *minis, t_parser *parser)
{
	char	*operand;

	if (!parser->exp_value[1])
	{
		operand = getenv("HOME");
		if (operand != NULL)
			cd_args(minis, operand);
	}
	else
		cd_args(minis, parser->exp_value[1]);
}

void	ft_export(t_minist *minis, char **vars)
{
	t_list	*node;
	char	*value;
	int		i;
	int		j;

	i = 0;
	if (!vars || !vars[i])
		ft_env(minis);
	while (vars && vars[i])
	{
		node = minis->env_list;
		value = ft_strdup(vars[i]);
		if (!value)
			return (set_error(minis->err, ERR_ALLOC, "ft_export")
				, (void )0);
		j = 0;
		while (value && value[j] && (ft_isalnum(value[j])
				|| value[j] == '_' || value[j] == '?') && value[j] != '=')
			j++;
		if (value && value[j] && value[j] == '=')
			find_node(minis, &node, &value);
		else
			free(value);
		i++;
	}
}

void	ft_unset(t_minist *minis, char **vars, int i)
{
	t_list	*node;
	size_t	arg_size;
	size_t	env_size;

	node = minis->env_list;
	arg_size = env_var_len(vars[i]);
	while (node && vars && vars[i])
	{
		env_size = env_var_len((char *)node->content);
		if (arg_size == env_size && node->content
			&& ft_strncmp(vars[i]
				, (const char *)node->content, env_size) == 0)
		{
			free(node->content);
			ft_lstdelone(&(minis->env_list), node);
			node = minis->env_list;
		}
		node = node->next;
	}
	if (minis->env && minis->env != NULL)
		free_dtab(minis->env);
	minis->env = env_list_into_char(minis);
	if (vars[i + 1] && vars[i + 1] != NULL)
		ft_unset(minis, vars, i + 1);
}
