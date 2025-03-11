/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniparser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:33:07 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/17 13:15:32 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIPARSER_H
# define MINIPARSER_H

typedef enum e_token_type
{
	T_WORD = 0,
	T_VAR = 1,
	T_S_QUOTE = 2,
	T_D_QUOTE = 3,
	T_PIPE = 4,
	T_REDIR_IN = 5,
	T_REDIR_OUT = 6,
	T_REDIR_HDOC = 7,
	T_REDIR_OUT_APP = 8,
	T_END = 9
}	t_token_type;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}	t_io_type;

typedef enum e_lexstate
{
	L_DEFAULT = 0,
	L_IN_SQUOTE = 1,
	L_IN_DQUOTE = 2,
	L_IN_VAR = 3,
	L_IN_COMMAND = 4
}	t_lexstate;

typedef enum e_quotes
{
	QUOTES_S = 0,
	QUOTES_D = 1
}	t_quotes;

typedef struct s_tokens
{
	char			*data;
	t_token_type	type_len;
	t_token_type	type_data;
	t_lexstate		state;
	struct s_tokens	*next;
}					t_tokens;

typedef struct s_inout
{
	t_io_type		type;
	char			*value;
	int				fd_here_doc;
	struct s_inout	*next;
}					t_inout;

typedef struct s_parser
{
	t_inout			*io;
	pid_t			pid;
	char			*value;
	char			**exp_value;
	int				cmd_num;
	bool			pipe;
	bool			redir_in;
	struct s_parser	*left;
	struct s_parser	*right;
}					t_parser;

typedef struct s_list		t_list;
typedef struct s_minist		t_minist;

/* ************************************************************************** */
/* 																			  */
/* 									utils									  */
/* 																			  */
/* ************************************************************************** */

void		set_token_default(t_tokens **token_ptr);

/**
 * @brief returns string representation of given token type
 *
 * @param type
 * @return char*
 */
char		*token_type_name(t_token_type type);

/**
 * @brief returns string representation of given io type
 * 
 * @param type 
 * @return char* 
 */
char		*io_type_name(t_io_type type);

void		ft_exit_failure(t_minist *minis);

bool		ft_ctrl_d(t_minist *minis);

/* ************************************************************************** */
/* 																			  */
/* 									translate_utils							  */
/* 																			  */
/* ************************************************************************** */

t_parser	*new_parser_node(int reset);

void		add_node(t_minist *minis, t_parser **parser, int role);

bool		add_io_node(t_minist *minis, t_parser **parser, t_inout **io_ptr);

int			get_cmd_len(t_tokens *tokens);

void		translate_error(t_minist *minis, t_tokens *token_ptr);

/* ************************************************************************** */
/* 																			  */
/* 									translate								  */
/* 																			  */
/* ************************************************************************** */

void		handle_command(t_minist *minis, t_parser **parser,
				t_tokens **tokens);

void		handle_redir(t_minist *minis, t_parser **parser, t_tokens **tokens);

void		handle_pipe(t_minist *minis, t_parser **parser);

void		handle_parser(t_minist *minis, t_tokens **token_ptr,
				t_parser **parser_ptr);

/**
 * @brief translates t_tokens list to t_parser_node list
 *
 * @param minis
 */
void		translate_tokens(t_minist *minis);

/* ************************************************************************** */
/* 																			  */
/* 									tokens_utils							  */
/* 																			  */
/* ************************************************************************** */

int			ft_count(char *word, int i, int role);

void		increment_two_int(int *k, int *len);

void		next_token(t_minist *minis, t_tokens **token_ptr, int i, int role);

void		split_space(t_minist *minis, t_tokens **token_ptr, int i);

void		check_var_space(t_minist *minis, t_tokens **token_ptr);

/* ************************************************************************** */
/* 																			  */
/* 									tokens_vars_utils						  */
/* 																			  */
/* ************************************************************************** */

char		*no_var(int name_count);

/* ************************************************************************** */
/* 																			  */
/* 									tokens_vars_setfind						  */
/* 																			  */
/* ************************************************************************** */

t_list		*find_var(t_minist *minis, char *word, int name_count);

/**
 * @brief joins what's before the variable with the content of the variable
 * 
 * @param minis 
 * @param word 
 * @param tmp 
 * @return char* 
 */
char		*set_tmp_var(t_minist *minis, char *word, char *tmp);

bool		set_res(t_minist *minis, char **res, char **tmp_var);

int			check_var(char *word);

/* ************************************************************************** */
/* 																			  */
/* 									tokens_vars								  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief evaluates if the variable exists, and if so returs it's content
 * and if not returns ft_strdup("")
 * 
 * @param minis 
 * @param word 
 * @return char* 
 */
char		*var_no_quotes(t_minist *minis, char *word);

/**
 * @brief if there's nothing before the variable, sets the content
 * of the variable to res
 * 
 * @param minis 
 * @param res 
 */
void		count_not_zero(t_minist *minis, char **res);

/**
 * @brief if there is something before the variable, sets res with
 * the content of the variable
 * 
 * @param minis 
 * @param res 
 */
void		count_zero(t_minist *minis, char **res);

/**
 * @brief sets res at before variable plus content of
 * the variable (what count_not_zero sets in res)
 * plus what was after the variable
 * 
 * @param minis 
 * @param before_var 
 * @param res 
 */
void		after_var(t_minist *minis, char *before_var, char **res);

/**
 * @brief joins what's before a variable with the content of the variable
 * and what's after a variable, including other variables,
 * until the end of the quotes or the word
 * 
 * @param minis 
 * @param word 
 */
void		var_quotes(t_minist *minis, char **word);

/* ************************************************************************** */
/* 																			  */
/* 									tokens_quotes							  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief joins what's before the last quotes curruntly found
 * (after rm_f_quotes has done the same with the first quotes)
 * with what's after the quotes
 * 
 * @param word 
 * @param new_word 
 * @param i 
 * @param j 
 */
void		old_word_l(char **word, char *new_word, int i, int j);

void		rm_l_quote(t_minist *minis, char **word, int i, t_quotes role);

/**
 * @brief joins what's before the first quotes curruntly found  with what's
 * after the quotes
 * 
 * @param word 
 * @param tmp 
 * @param i 
 */
void		old_word_f(char **word, char *tmp, int i);

void		rm_f_quote(t_minist *minis, char **word, int i, t_quotes role);

void		handle_quotes(t_minist *minis, char **word, t_quotes role);

/* ************************************************************************** */
/* 																			  */
/* 									tokens_data								  */
/* 																			  */
/* ************************************************************************** */

void		handle_s_quotes(t_minist *minis, char **word);

void		handle_d_quotes(t_minist *minis, char **word);

void		handle_word_default(t_minist *minis, t_lexstate state, char **word);

void		handle_word(t_minist *minis, t_lexstate state, char **word);

void		continue_data(t_minist *minis, t_tokens *token_ptr, char **word);

/* ************************************************************************** */
/* 																			  */
/* 									tokens_recursive_len					  */
/* 																			  */
/* ************************************************************************** */

void		continue_len(t_minist *minis, t_tokens *token_ptr, int *k);

void		check_continue_len(t_minist *minis, t_tokens *token_ptr, int *k);

void		rec_len(t_minist *minis, t_tokens *token_ptr, int *k);

/* ************************************************************************** */
/* 																			  */
/* 									tokens_len								  */
/* 																			  */
/* ************************************************************************** */

void		set_token_end(t_minist *minis, t_tokens *token_ptr);

void		token_len(t_minist *minis, t_tokens *token_ptr, int *k);

void		set_token_len_word(t_minist *minis, t_tokens *token_ptr, int *k);

void		set_token_len_quotes(t_minist *minis, t_tokens *token_ptr, int *k);

void		set_token_len(t_minist *minis, t_tokens *token_ptr, int *k);

/* ************************************************************************** */
/* 																			  */
/* 									tokens									  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief 
 * 
 * @param minis 
 * @param token_ptr 
 * @param i 
 * @return true 
 * @return false 
 */
bool		check_redirs(t_minist *minis, t_token_type *type,
				char *word, int i);

/**
 * @brief 
 * 
 * @param minis 
 * @param token_ptr 
 * @param i 
 */
void		check_tokens(t_minist *minis, t_token_type *type,
				char *word, int *i);

/**
 * @brief Set the word data object
 * 
 * @param minis 
 * @param token_ptr 
 * @param word 
 * @param i 
 */
void		set_word_data(t_minist *minis, t_tokens *token_ptr, char **word);

/**
 * @brief Set the token data object
 * 
 * @param minis  //
 * @param token_ptr 
 * @param i 
 * @return char* 
 */
char		*set_token_data(t_minist *minis, t_tokens *token_ptr, int *i);

/**
 * @brief Set the tokens object
 * 
 * @param minis 
 */
void		set_tokens(t_minist *minis);

/* ************************************************************************** */
/* 																			  */
/* 									miniparser								  */
/* 																			  */
/* ************************************************************************** */

void		set_var_cwd(t_minist *minis, char **var, char **var_val);

void		set_vars(t_minist *minis);

/**
 * @brief 
 * 
 * @param minis 
 */
void		lexer(t_minist *minis);

/**
 * @brief 
 * 
 * @param minis 
 * @return true 
 * @return false 
 */
bool		parser(t_minist *minis);

#endif
