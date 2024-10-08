/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:13:32 by jlarieux          #+#    #+#             */
/*   Updated: 2024/09/07 11:10:10 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minist	s_minis;

	s_minis.arg_c_or = argc;
	s_minis.args = argv;
	s_minis.env = envp;
	pipex(&s_minis);
	free(s_minis.infile); //to rm
	free(s_minis.outfile); //to rm
	return (0);
}
