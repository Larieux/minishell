/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibuilt_ins_actions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:17:37 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 09:11:29 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i + 1])
		i++;
	if (i == 0)
		return ;
	if (str && str[i] && str[1]
		&& ft_strncmp(str[1], "-n", 2) == 0 && i != 1)
		handle_res(str);
	else if (str && str[i])
	{
		res = set_echo(str, 1);
		ft_putstr_fd(res, STDOUT_FILENO);
		free (res);
	}
}

void	ft_pwd(void)
{
	char	*res;

	res = getcwd(NULL, 0);
	printf("%s\n", res);
	free(res);
}

void	ft_env(t_minist *minis)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	res = NULL;
	while (minis->env && minis->env[i])
	{
		tmp = ft_strjoin(res, minis->env[i]);
		free(res);
		res = ft_strjoin(tmp, "\n");
		free(tmp);
		i++;
	}
	printf("%s", res);
	free(res);
}
