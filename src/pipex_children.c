/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:25:38 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/06 10:58:16 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child(t_minist *s_minis, int *fd_pipe)
{
	char	**cmd;
	int		fd;

	if (ft_strncmp(s_minis->outfile, "/dev/stdout", 12)
		&& ft_strlen(s_minis->outfile) == 12)
		fd = STDOUT_FILENO;
	else
	{
		if (s_minis->here_doc == 1)
			fd = ft_exec_open(s_minis->outfile, 0);
		else
			fd = ft_exec_open(s_minis->outfile, 1);
	}
	if (fd == -1)
		fd_error(s_minis->outfile);
	cmd = ft_split(s_minis->args[s_minis->arg_c], ' ');
	if (!cmd || cmd == NULL || cmd[0] == NULL)
		exit_malloc(cmd);
	dup_and_close(fd, fd_pipe, 0, 0);
	free (s_minis->infile);
	free (s_minis->outfile);
	if (check_built_ins(s_minis))
		exit(EXIT_SUCCESS);
	find_cmd(s_minis, cmd);
}

void	inter_child(t_minist *s_minis, int *fd_pipe, int fd_prev_out)
{
	char	**cmd;

	cmd = ft_split(s_minis->args[s_minis->arg_c], ' ');
	if (!cmd || cmd == NULL || cmd[0] == NULL)
		exit_malloc(cmd);
	dup_and_close(-1, fd_pipe, fd_prev_out, 1);
	free (s_minis->infile);
	free (s_minis->outfile);
	if (check_built_ins(s_minis))
		exit(EXIT_SUCCESS);
	find_cmd(s_minis, cmd);
}

void	child2(t_minist *s_minis, int *fd_pipe, int fd_prev_out)
{
	char	**cmd;
	int		fd;

	if (s_minis->here_doc == 1)
		fd = open(s_minis->infile, O_RDONLY, 0644);
	else
		fd = open(s_minis->infile, O_RDONLY, 0644);
	if (fd == -1)
	{
		if (s_minis->here_doc == 1)
			fd_error(s_minis->infile);
		else
			fd_error(s_minis->infile);
	}
	cmd = ft_split(s_minis->args[s_minis->first_cmd], ' ');
	if (!cmd || cmd == NULL || cmd[0] == NULL)
		exit_malloc(cmd);
	dup_and_close(fd, fd_pipe, fd_prev_out, 2);
	free (s_minis->infile);
	free (s_minis->outfile);
	if (check_built_ins(s_minis))
		exit(EXIT_SUCCESS);
	find_cmd(s_minis, cmd);
}
