/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:24:38 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/05 18:08:42 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec_open(char *str, int role)
{
	int	fd;

	if (!(ft_strncmp(str, "/dev/stdout", 12) && ft_strlen(str) == 12))
	{
		if (role == 0)
			fd = open(str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			fd = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		return (fd);
	}
	return (STDOUT_FILENO);
}

void	free_dtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] == NULL)
		i++;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	exit_malloc(char **dtab)
{
	write(2, "malloc error or cmd '' not found\n", 34);
	free(dtab);
	exit(EXIT_FAILURE);
}

void	exit_dfree_malloc(char **tab)
{
	write(2, "malloc error or cmd '' not found\n", 34);
	free_dtab(tab);
	exit(EXIT_FAILURE);
}

void	fd_error(char *str)
{
	char	*error;
	char	*error2;
	char	*error3;
	int		errlen;

	error = ft_strjoin(str, " : ");
	error2 = ft_strjoin(error, strerror(errno));
	error3 = ft_strjoin(error2, "\n");
	errlen = ft_strlen(error3);
	write(2, error3, errlen);
	free(error);
	free(error2);
	free(error3);
	exit(EXIT_FAILURE);
}
