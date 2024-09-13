/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:26:13 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/13 09:07:21 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>//

char	*test_old_line_gnl(char *buffer)
{
	char	*line;
	char	*ptr_n;
	int		i;

	i = 0;
	ptr_n = ft_strchr(buffer, '\n');
	if (ptr_n != NULL)
	{
		while (ptr_n[i + 1] != '\0')
		{
			buffer[i] = ptr_n[i + 1];
			i++;
		}
		buffer[i] = '\0';
	}
	line = ft_strjoin(buffer, "");
	if (!line)
		return (NULL);
	return (line);
}

bool	test_new_line_gnl(char *line)
{
	char	*ptr_n;
	char	*ptr_0;

	if (!line || line == NULL)
		return (false);
	ptr_n = ft_strchr(line, '\n');
	if (ptr_n != NULL)
	{
		ptr_n[1] = '\0';
		return (true);
	}
	return (false);
}

char	*make_line_gnl(char *line, char *buffer, int fd, ssize_t size)
{
	char	*tmp_line;
	ssize_t	n;

	n = size;
	tmp_line = ft_strjoin(line, "");
	free (line);
	while (!test_new_line_gnl(tmp_line) && n == size)
	{
		n = read(fd, buffer, size);
		if (n == -1)
			return (free(line), NULL);
		buffer[n] = '\0';
		line = ft_strjoin(tmp_line, buffer);
		free(tmp_line);
		if (!line || line[0] == '\0')
			return (free(line), NULL);
		tmp_line = ft_strjoin(line, "");
		free(line);
		if (!tmp_line || tmp_line[0] == '\0')
			return (free(tmp_line), NULL);
	}
	return (tmp_line);
}

char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD] [BUFFER_SIZE + 1] = {0};
	char		*tmp_line;
	char		*line;

	if (fd == -1 || BUFFER_SIZE == 0 || fd >= MAX_FD)
		return (NULL);
	line = test_old_line_gnl(buffer[fd]);
	if (!line)
		return(NULL);
	tmp_line = make_line_gnl(line, buffer[fd], fd, BUFFER_SIZE);
	if (!tmp_line || tmp_line == NULL)
		return (free(tmp_line), NULL);
	line = ft_strjoin(tmp_line, "");
	free(tmp_line);
	if (!line || line[0] == '\0')
		return (NULL);
	return (line);
}
