/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:14:27 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/16 17:13:48 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PIPE_READ	0
# define PIPE_WRITE	1
# define READ	2
# define WRITE	3

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <stdio.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minicolors.h"
# include "miniparser.h"
# include "minibuilt_ins.h"
# include "miniexec.h"
# include "libft.h"

typedef enum e_error_type
{
	NO_ERR = 0,
	ERR_SYNTAX = 1,
	ERR_CMD = 2,
	ERR_IDENT = 3,
	ERR_ISDIR = 4,
	ERR_ALLOC = 5,
	ERR_SIG = 6,
	ERR_ACCESS = 7,
	ERR_NOT_EXIST = 8,
	ERR_FD = 9,
	ERR_HEREDOC = 10,
	ERR_NOQUOTE = 11,
	ERR_UNKNOWN = 12,
}	t_error_type;

typedef enum e_ministate
{
	READLINE = 0,
	EXECUTION = 1,
	HEREDOC = 2,
}	t_ministate;

typedef enum e_token_type	t_token_type;

typedef enum e_inout_type	t_inout_type;

typedef enum e_lexstate		t_lexstate;

typedef struct s_tokens		t_tokens;

typedef struct s_inout		t_inout;

typedef struct s_parser		t_parser;

typedef struct s_exec		t_exec;

typedef struct s_error
{
	t_error_type	code;
	char			*msg;
}					t_error;

typedef struct s_minist
{
	char		**env;
	char		*line;
	int			exit_code;
	int			token_i;
	int			token_end;
	int			fd_here_doc;
	t_list		*env_list;
	t_tokens	*tokens;
	t_parser	*parser;
	t_exec		*exec;
	t_error		*err;
	t_ministate	state;
}				t_minist;

/* ************************************************************************** */
/* 																			  */
/* 									errors_set_show							  */
/* 																			  */
/* ************************************************************************** */

bool		show_error(t_error *err);

int			set_error(t_error *err, t_error_type type, char *s);

bool		set_show_error(t_error *err, t_error_type type, char *s);

/* ************************************************************************** */
/* 																			  */
/* 									errors									  */
/* 																			  */
/* ************************************************************************** */

int			errno_to_code(int n);

char		*get_error(t_error_type t);

char		*token_name(t_token_type type);

bool		handle_errors(t_minist *minis);

/* ************************************************************************** */
/* 																			  */
/* 									frees									  */
/* 																			  */
/* ************************************************************************** */

void		free_tokens(t_tokens **token);

/**
 * @brief 
 * 
 * @param minis 
 */
void		free_parser(t_minist *minis);

void		free_node(t_parser *parser);

void		free_env(char **env);

void		free_minist(void);

/* ************************************************************************** */
/* 																			  */
/* 									utils									  */
/* 																			  */
/* ************************************************************************** */

bool		str_alloc(t_minist *minis, char **str, char *msg, int size);

t_minist	*get_minist(void);

/* ************************************************************************** */
/* 																			  */
/* 									signals									  */
/* 																			  */
/* ************************************************************************** */

void		sig_int_handler(int sig);

void		set_signals(int on);

void		set_signal_handlers(void);

void		sig_int_heredoc_handler(int sig);

/* ************************************************************************** */
/* 																			  */
/* 									init									  */
/* 																			  */
/* ************************************************************************** */

void		env_to_node(t_minist *minis, char **envp, int *i);

void		no_envp(t_minist *minis);

void		set_env(t_minist *minis, char **envp, int *i);

void		init_env(t_minist *minis, char **envp);

void		init_minis(t_minist *minis, char **envp);

#endif
