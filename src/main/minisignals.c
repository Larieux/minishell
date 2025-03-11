/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisignals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:02:38 by mlarieux          #+#    #+#             */
/*   Updated: 2025/03/11 13:02:40 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int_handler(int sig)
{
	t_ministate	state;

	state = READLINE;
	if (get_minist())
	{
		state = get_minist()->state;
		if (state != HEREDOC)
			get_minist()->exit_code = 128 + sig;
	}
	if (state == READLINE)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_int_heredoc_handler(int sig)
{
	t_minist	*minis;

	write(1, "\n", 1);
	minis = get_minist();
	if (minis->fd_here_doc != -1)
		close(minis->fd_here_doc);
	minis->fd_here_doc = open("/tmp/tmp_heredoc",
			O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (minis->fd_here_doc != -1)
		close(minis->fd_here_doc);
	free_minist();
	free(minis);
	exit(128 + sig);
}

void	set_signals(int on)
{
	if (on)
		signal(SIGINT, sig_int_handler);
	else
		signal(SIGINT, SIG_IGN);
}

void	set_signal_handlers(void)
{
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
}
