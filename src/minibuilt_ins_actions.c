/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibuilt_ins_actions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:17:37 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/06 19:16:34 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(char *str, bool n)
{
	char	**dtmp;
	char	*tmp;
	char	*res;
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_strdup(str);
	ptr = ft_strchr(tmp, '\n');
	while (ptr != NULL)
	{
		i++;
		ptr++;
		ptr = ft_strchr(ptr, '\n');
	}
	dtmp = ft_split(tmp, '\n');
	free(tmp);
	tmp = ft_strjoin(dtmp[j], "\\n");
	free(dtmp[j]);
	while (j < i)
	{
		dtmp[j] = ft_strjoin(tmp, dtmp[j + 1]);
		free(tmp);
		if (j < i - 1)
		{
			tmp = ft_strjoin(dtmp[j + 1], "\\n");
			free(dtmp[j + 1]);
		}
		j++;
	}
	if (n == true)
		res = ft_strdup(dtmp[j - 1]);
	else
		res = ft_strjoin(dtmp[j - 1], "\n");
	free(dtmp);
	ft_putstr_fd(res, STDOUT_FILENO);
	return (free(res), 0);
}
