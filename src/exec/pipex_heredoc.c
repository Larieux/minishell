/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:25:13 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 10:52:14 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_heredoc(t_minist *minis, t_inout *io, char **line)
{
	int		line_len;

	minis->fd_here_doc = open("/tmp/tmp_heredoc",
			O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (minis->fd_here_doc == -1)
		fd_error(minis, "/tmp/tmp_heredoc");
	*line = readline("> ");
	line_len = ft_strlen(*line);
	while (*line == NULL || ft_strncmp(*line,
			io->value, line_len) != 0
		|| ft_strncmp(*line,
			io->value, minis->exec->eof_len) != 0)
	{
		if (*line == NULL
			&& !set_show_error(minis->err, ERR_HEREDOC, io->value))
			break ;
		write(minis->fd_here_doc, *line, line_len);
		write(minis->fd_here_doc, "\n", 1);
		free(*line);
		*line = readline("> ");
		if (*line != NULL)
			line_len = ft_strlen(*line);
		else
			line_len = 0;
	}
}

void	init_heredoc(t_minist *minis, t_inout *io)
{
	char	*line;
	pid_t	pid;

	minis->state = HEREDOC;
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, sig_int_heredoc_handler);
		exec_heredoc(minis, io, &line);
		free(line);
		close (minis->fd_here_doc);
		free_minist();
		free(minis);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
}
