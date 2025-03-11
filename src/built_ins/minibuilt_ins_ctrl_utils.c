/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibuilt_ins_ctrl_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:23:59 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 17:41:44 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_args(t_minist *minis, char *operand)
{
	char	*old_pwd;
	char	**to_export;

	old_pwd = getcwd(NULL, 0);
	to_export = malloc(2 * sizeof(char *));
	if (!to_export)
		return (set_error(minis->err, ERR_ALLOC, "cd_args_1"), (void)0);
	to_export[0] = ft_strjoin("OLDPWD=", old_pwd);
	if (!to_export[0])
		return (free(to_export)
			, set_error(minis->err, ERR_ALLOC, "cd_args_1"), (void)0);
	to_export[1] = NULL;
	if (chdir(operand) == -1)
		set_error(minis->err, ERR_NOT_EXIST, operand);
	else
		ft_export(minis, &(to_export[0]));
	free(to_export[0]);
	free(old_pwd);
	old_pwd = getcwd(NULL, 0);
	to_export[0] = ft_strjoin("PWD=", old_pwd);
	ft_export(minis, &(to_export[0]));
	free(to_export[0]);
	free(to_export);
	free(old_pwd);
}

size_t	env_var_len(char *s)
{
	size_t		i;

	i = 0;
	while (s && s[i] && s[i] != '=')
		i++;
	return (i);
}

char	**env_list_into_char(t_minist *minis)
{
	t_list	*node;
	char	**env;
	int		size;
	int		i;

	node = minis->env_list;
	size = ft_lstsize(minis->env_list);
	env = malloc((size + 1) * sizeof(char *));
	if (!env)
		return (set_error(minis->err, ERR_ALLOC, "env_list"), NULL);
	i = 0;
	while (node && node != NULL)
	{
		env[i] = ft_strdup((char *)(node->content));
		if (!env[i])
		{
			env[i] = NULL;
			return (free_dtab(env)
				, set_error(minis->err, ERR_ALLOC, "env_list"), NULL);
		}
		node = node->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	handle_node(t_minist *minis, t_list *node, char **value)
{
	if (node && node != NULL && node->content && node->content != NULL)
	{
		free(node->content);
		node->content = *value;
		if (minis->env && minis->env != NULL)
			free_dtab(minis->env);
		minis->env = env_list_into_char(minis);
		return ;
	}
	node = ft_lstnew(*value);
	if (!node)
		return (free(*value)
			, set_error(minis->err, ERR_ALLOC, "ft_export"), (void)0);
	if (!minis->env_list || minis->env_list == NULL)
		minis->env_list = node;
	else
		ft_lstadd_back(&(minis->env_list), node);
	if (minis->env && minis->env != NULL)
		free_dtab(minis->env);
	minis->env = env_list_into_char(minis);
}

void	find_node(t_minist *minis, t_list **node, char **value)
{
	int		len;
	int		cont_len;

	len = check_var(*value);
	if (*node && *node != NULL && (*node)->content)
		cont_len = check_var((char *)(*node)->content);
	while ((*node) != NULL
		&& !(len == cont_len
			&& ft_strncmp((const char *)((*node)->content)
			, *value, cont_len) == 0))
	{
		(*node) = (*node)->next;
		if ((*node) != NULL && (*node)->content)
			cont_len = check_var((char *)(*node)->content);
	}
	handle_node(minis, *node, value);
}
