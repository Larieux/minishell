/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:26:13 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/17 15:35:02 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	test_old_line_gnl(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] && buffer[i] == '\n')
	{
		i++;
		while (buffer[i])
		{
			buffer[j] = buffer[i];
			i++;
			j++;
		}
		buffer[j] = '\0';
		return (true);
	}
	buffer[0] = '\0';
	return (false);
}

bool	test_new_line_gnl(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
	{
		line[i + 1] = '\0';
		return (true);
	}
	return (false);
}

char	*make_line_gnl(char *line, char *buffer, int fd, ssize_t size)
{
	ssize_t		n;

	n = size;
	while (!test_new_line_gnl(line) && n == size)
	{
		n = read(fd, buffer, size);
		if (n == -1)
			return (free (line), NULL);
		buffer[n] = '\0';
		line = ft_strjoin_gnl(line, buffer);
		if (!line || line[0] == '\0')
			return (free (line), NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD][BUFFER_SIZE + 1] = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (test_old_line_gnl(buffer[fd]))
	{
		line = ft_strjoin_gnl(line, buffer[fd]);
		if (line == NULL)
			return (free (line), NULL);
	}
	line = make_line_gnl(line, buffer[fd], fd, BUFFER_SIZE);
	if (line == NULL)
		return (free (line), NULL);
	line = ft_strjoin_gnl(line, "");
	if (line == NULL || line[0] == '\0')
		return (free (line), NULL);
	return (line);
}
