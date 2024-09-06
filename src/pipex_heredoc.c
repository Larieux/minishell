/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:25:13 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/06 11:24:02 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_heredoc(char **line, int *fd, int *line_len)
{
	if (*line != NULL)
		write(1, "> ", 2);
	write(*fd, *line, *line_len);
	free(*line);
	*line = get_next_line(0);
	if (*line != NULL)
		*line_len = ft_strlen(*line);
	else
		*line_len = 0;
}

void	init_heredoc(t_minist *s_minis)
{
	char	*line;
	int		fd;
	int		line_len;

	fd = open("/tmp/tmp_heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		fd_error("/tmp/tmp_heredoc");
	}
	write(1, "> ", 2);
	line = get_next_line(0);
	line_len = ft_strlen(line);
	while (line == NULL || ft_strncmp(line, s_minis->args[2], line_len - 1) != 0
		|| ft_strncmp(line, s_minis->args[2], s_minis->eof_len) != 0)
		exec_heredoc(&line, &fd, &line_len);
	free(line);
	s_minis->infile = ft_strdup("/tmp/tmp_heredoc");
	close (fd);
}
