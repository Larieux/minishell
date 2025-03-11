/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minifrees.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:50:37 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/12 10:54:38 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens **token)
{
	t_tokens	*tmp;

	while (*token)
	{
		if ((*token)->data)
			free ((*token)->data);
		tmp = (*token);
		*token = (*token)->next;
		free (tmp);
	}
}

void	free_node(t_parser *node)
{
	int			i;
	t_inout		*io;

	if (!node || node == NULL)
		return ;
	while (node->io)
	{
		if (node->io->value)
			free(node->io->value);
		io = node->io->next;
		free(node->io);
		node->io = io;
	}
	if (node->value)
		free(node->value);
	i = 0;
	while (node->exp_value && node->exp_value[i])
	{
		free(node->exp_value[i]);
		i++;
	}
	free(node->exp_value);
}

void	free_parser(t_minist *minis)
{
	t_parser	*tmp;

	while (minis->parser)
	{
		free_node(minis->parser);
		tmp = minis->parser;
		minis->parser = minis->parser->right;
		free(tmp);
	}
	minis->parser = NULL;
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	free_minist(void)
{
	t_minist	*minis;

	minis = get_minist();
	if (!minis)
		return ;
	if (minis->tokens)
		free_tokens(&minis->tokens);
	if (minis->parser)
		free_parser(minis);
	if (minis->exec)
		free(minis->exec);
	if (minis->err)
		free(minis->err);
	if (minis->env_list)
	{
		ft_lstclear(&minis->env_list);
		free(minis->env_list);
	}
	if (minis->env)
		free_env(minis->env);
	free(minis->line);
	rl_clear_history();
}
