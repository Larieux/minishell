/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniinit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:05:40 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 17:46:02 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_to_node(t_minist *minis, char **envp, int *i)
{
	t_list	*node;
	char	*var;

	var = ft_strdup(envp[*i]);
	if (!var)
		return (set_error(minis->err, ERR_ALLOC, "handle_command")
			, (void )0);
	node = ft_lstnew((void *)var);
	if (!node)
		return (free(var), set_error(minis->err, ERR_ALLOC, "handle_command")
			, (void )0);
	if (!minis->env_list || minis->env_list == NULL)
		minis->env_list = node;
	else
		ft_lstadd_back(&(minis->env_list), node);
	*i += 1;
}

void	no_envp(t_minist *minis)
{
	minis->env = malloc((2) * sizeof(char *));
	if (!minis->env)
		return (set_error(minis->err, ERR_ALLOC, "init_env_2"), (void )0);
	minis->env[0] = ft_strdup("?=0");
	minis->env[1] = NULL;
	set_vars(minis);
}

void	set_env(t_minist *minis, char **envp, int *i)
{
	minis->env[*i] = ft_strdup(envp[*i]);
	if (!minis->env[*i])
		return (free_env(minis->env)
			, set_error(minis->err, ERR_ALLOC, "init_env_4"), (void )0);
	*i += 1;
}

void	init_env(t_minist *minis, char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		env_to_node(minis, envp, &i);
	if ((!envp && !envp[i]) || i == 0)
		return (no_envp(minis), (void)0);
	else
		minis->env = malloc((i + 1) * sizeof(char *));
	if (!minis->env)
		return (set_error(minis->err, ERR_ALLOC, "init_env_3"), (void )0);
	i = 0;
	while (envp && envp[i])
		set_env(minis, envp, &i);
	minis->env[i] = NULL;
	set_vars(minis);
}

void	init_minis(t_minist *minis, char **envp)
{
	minis->line = NULL;
	minis->err = malloc(sizeof(t_error));
	if (!minis->err)
		return ;
	minis->err->code = NO_ERR;
	minis->exit_code = 0;
	init_env(minis, envp);
	minis->parser = NULL;
	minis->tokens = NULL;
	minis->state = READLINE;
}
