/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:13:32 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/06 19:18:58 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minist	s_minis;
	int			fd_out;

	s_minis.arg_c_or = argc;
	s_minis.args = argv;
	s_minis.env = envp;
	pipex(&s_minis);
	free(s_minis.infile);
	free(s_minis.outfile);
	return (0);
}
