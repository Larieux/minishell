/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:26:13 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/12 13:43:04 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*test_old_line_gnl(char *old_line)
{
	char	*ptr;
	char	*line;
	int		len;

	ptr = ft_strchr(old_line, '\n');
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
	if (!line || line == NULL)
		return (true);
	if (ft_strchr(line, '\n') != NULL)
		return (true);
	return (false);
}

char	*make_line_gnl(char *line, char *buffer, int fd, size_t size)
{
	char	*tmp_line;
	size_t	n;

	n = size;
	while (!test_new_line_gnl(line) && n == size)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		buffer[n] = '\0';
		tmp_line = ft_strjoin(line, buffer);
		if (!tmp_line)
			return (NULL);
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
	static char	buffer[BUFFER_SIZE] = {0};
	char		*old_line;
	char		*line;

	if (fd == -1 || BUFFER_SIZE == 0 || fd >= MAX_FD)
		return (NULL);
	old_line = ft_strjoin (buffer, "");
	if (!old_line)
		return (NULL);
	line = test_old_line_gnl(old_line);
	old_line = make_line_gnl(line, buffer, fd, BUFFER_SIZE);
	if (!old_line)
		return (NULL);
	line = ft_strjoin(old_line, "");
	if (!line)
		return (NULL);
	return (free(old_line), line);
}
