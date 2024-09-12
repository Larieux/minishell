/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:26:13 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/12 16:48:32 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*test_old_line_gnl(char *old_line)
{
	char	*ptr;
	char	*line;
	int		len;

	ptr = ft_strchr(old_line, '\n');
	if (ptr == NULL)
		return(old_line);
	len = ft_strlen(ptr);
	line = (char *)malloc (len * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, ptr, len);
	free(old_line);
	return (line);
}

bool	test_new_line_gnl(char *line)
{
	char	*ptr;
	if (!line || line == NULL)
		return (true);
	ptr = ft_strchr(line, '\n');
	if (ptr != NULL)
	{
		ptr++;
		*ptr = '\0';
		return (true);
	}
	return (false);
}

char	*make_line_gnl(char *line, char *buffer, int fd, size_t size)
{
	char	*tmp_line;
	size_t	n;

	n = size;
	while (!test_new_line_gnl(line) && n == size)
	{
		n = read(fd, buffer, size);
		if (n == -1)
			return (free(line), NULL);
		buffer[n] = '\0';
		tmp_line = ft_strjoin(line, buffer);
		if (!tmp_line || tmp_line[0] == '\0')
			return (free(tmp_line), free(line), NULL);
		free(line);
		line = ft_strjoin(tmp_line, "");
		if (!line)
			return (NULL);
		free(tmp_line);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD] [BUFFER_SIZE + 1] = {0};
	char		*old_line;
	char		*line;

	if (fd == -1 || BUFFER_SIZE == 0 || fd >= MAX_FD)
		return (NULL);
	old_line = ft_strjoin (buffer[fd], "");
	if (!old_line)
		return (NULL);
	line = test_old_line_gnl(old_line);
	if (line == NULL)
		return (free(line), NULL);
	old_line = make_line_gnl(line, buffer[fd], fd, BUFFER_SIZE);
	if (!old_line || old_line == NULL)
		return (free(old_line), NULL);
	line = ft_strjoin(old_line, "");
	if (!line)
		return (NULL);
	return (free(old_line), line);
}
