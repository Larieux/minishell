/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibuilt_ins_actions_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 09:01:05 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 09:07:06 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_res(char **str, char **res, char **tmp, int i)
{
	*res = ft_strjoin(*tmp, str[i]);
	free(*tmp);
	if (!(*res))
		return (set_error(get_minist()->err, ERR_ALLOC, "echo_res_1"), i++);
	i++;
	if (str[i])
	{
		*tmp = ft_strjoin(*res, " ");
		free(*res);
		if (!(*tmp))
			return (set_error(get_minist()->err, ERR_ALLOC, "echo_res_2")
				, i++);
	}
	return (i);
}

char	*set_echo(char **str, int i)
{
	char		*res;
	char		*tmp;

	res = NULL;
	if (!str || !str[i])
		return (NULL);
	tmp = ft_strdup("");
	if (!tmp)
		return (set_error(get_minist()->err, ERR_ALLOC, "set_echo_1"), NULL);
	if (i == 2)
	{
		while (str && str[i])
			i = echo_res(str, &res, &tmp, i);
		return (res);
	}
	else
	{
		while (str && str[i])
			i = echo_res(str, &res, &tmp, i);
		tmp = ft_strjoin(res, "\n");
		free (res);
		if (!tmp)
			return (set_error(get_minist()->err, ERR_ALLOC, "set_echo"), NULL);
		return (tmp);
	}
}

void	handle_res(char **str)
{
	char	*res;
	char	*ptr;

	res = set_echo(str, 2);
	ptr = ft_strrchr(res, '\n');
	if (ptr != NULL)
		*ptr = '\0';
	ft_putstr_fd(res, STDOUT_FILENO);
	free (res);
}

int	is_num_ok(char *s)
{
	int		i;
	char	c;

	i = 0;
	c = *(s + i);
	if (!ft_isdigit(c) && c != '-' && c != '+')
		return (0);
	i++;
	while (s && *(s + i))
	{
		c = *(s + i);
		if (!ft_isdigit(c) || i > 20)
			return (0);
		i++;
	}
	return (1);
}
