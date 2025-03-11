/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minierrors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:02:21 by mlarieux          #+#    #+#             */
/*   Updated: 2025/03/11 13:02:23 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_error(t_error_type type)
{
	static char	*error_message[] = {
	[NO_ERR] = "no error",
	[ERR_SYNTAX] = "syntax error near unexpected token",
	[ERR_CMD] = "command not found",
	[ERR_IDENT] = "not a valid identifier",
	[ERR_ISDIR] = "is a directory",
	[ERR_ALLOC] = "memory allocation error",
	[ERR_SIG] = "setting signal handler error",
	[ERR_ACCESS] = "permission denied",
	[ERR_NOT_EXIST] = "No such file or directory",
	[ERR_FD] = "bad fd",
	[ERR_HEREDOC] = "warning: here-document delimited by end-of-file (wanted `",
	[ERR_NOQUOTE] = "quote not closed",
	[ERR_UNKNOWN] = "unknown error"
	};

	if (type >= ERR_SYNTAX && type < ERR_UNKNOWN)
		return (error_message[type]);
	return (error_message[ERR_UNKNOWN]);
}

char	*token_name(t_token_type type)
{
	static char	*name[] = {
	[T_WORD] = "[WORD]",
	[T_VAR] = "[VAR]",
	[T_S_QUOTE] = "\'",
	[T_D_QUOTE] = "\"",
	[T_PIPE] = "|",
	[T_REDIR_IN] = "<",
	[T_REDIR_OUT] = ">",
	[T_REDIR_HDOC] = "<<",
	[T_REDIR_OUT_APP] = ">>"
	};

	if (type >= T_WORD && type <= T_REDIR_OUT_APP)
		return (name[type]);
	return ("");
}

int	errno_to_code(int n)
{
	int			errn;
	static int	code[] = {
	[0] = 0,
	[EPERM] = 1,
	[ENOENT] = 127,
	[ESRCH] = 1,
	[EINTR] = 1,
	[EIO] = 1,
	[ENXIO] = 1,
	[E2BIG] = 1,
	[ENOEXEC] = 1,
	[EBADF] = 1,
	[ECHILD] = 1,
	[EAGAIN] = 1,
	[ENOMEM] = 1,
	[EACCES] = 126
	};

	errn = n;
	if (n == -1)
		errn = errno;
	if (errn >= 0 && errn <= EACCES)
		return (code[errn]);
	return (1);
}
