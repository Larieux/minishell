/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:13:32 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 10:04:05 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minist	*minis;

	if (argc > 1)
		return (show_error(&(t_error){ERR_UNKNOWN,
				"wrong number of arguments"}), EXIT_FAILURE);
	(void)argv;
	minis = get_minist();
	set_signal_handlers();
	init_minis(minis, envp);
	while (parser(minis))
	{
		if (minis->err->code == ERR_ALLOC)
		{
			free_minist();
			if (minis)
				free(minis);
			return (-1);
		}
		else if (minis->err->code == NO_ERR)
			minis->exit_code = pipex(minis);
		if (minis->parser)
			free_parser(minis);
	}
	return (minis->exit_code);
}
