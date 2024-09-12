/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnlgit_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:48:05 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/12 16:34:23 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open("test", O_RDONLY, 0644);
	while (i < 9)
	{
		line = get_next_line(fd);
		printf("1%s\n", line);
		free(line);
		i++;
	}
}