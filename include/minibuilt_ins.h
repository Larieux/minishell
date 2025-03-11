/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibuilt_ins.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:05:35 by mlarieux          #+#    #+#             */
/*   Updated: 2025/03/11 12:38:45 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIBUILT_INS_H
# define MINIBUILT_INS_H

typedef struct s_minist			t_minist;
typedef struct s_parser			t_parser;

typedef enum e_check_built_in
{
	B_I_CHECK = 0,
	B_I_EXECUTE = 1,
}	t_check_built_in;

/* ************************************************************************** */
/* 																			  */
/* 									minibuilt_ins_actions_utils				  */
/* 																			  */
/* ************************************************************************** */

int		echo_res(char **str, char **res, char **tmp, int i);

char	*set_echo(char **str, int i);

void	handle_res(char **str);

int		is_num_ok(char *s);

/* ************************************************************************** */
/* 																			  */
/* 									minibuilt_ins_actions					  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief writes in the stdout the arguments given to it
 * 
 * @param str 
 * @param n 
 */
void	ft_echo(char **str);

/**
 * @brief prints the current working directory
 * 
 */
void	ft_pwd(void);

/**
 * @brief prints the environment variables
 * 
 * @param minis 
 */
void	ft_env(t_minist *minis);

/* ************************************************************************** */
/* 																			  */
/* 									minibuilt_ins_ctrl_utils				  */
/* 																			  */
/* ************************************************************************** */

void	cd_args(t_minist *minis, char *operand);

size_t	env_var_len(char *s);

/**
 * @brief 
 * 
 * @param minis 
 */
char	**env_list_into_char(t_minist *minis);

void	handle_node(t_minist *minis, t_list *node, char **value);

void	find_node(t_minist *minis, t_list **node, char **value);

/* ************************************************************************** */
/* 																			  */
/* 									minibuilt_ins_ctrl						  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief 
 * 
 * @param parser 
 */
void	ft_cd(t_minist *minis, t_parser *parser);

/**
 * @brief 
 * 
 * @param minis 
 */
void	ft_export(t_minist *minis, char **vars);

/**
 * @brief 
 * 
 * @param minis 
 */
void	ft_unset(t_minist *minis, char **vars, int i);

/* ************************************************************************** */
/* 																			  */
/* 									minibuilt_ins_exit						  */
/* 																			  */
/* ************************************************************************** */

void	handle_exit_no_arg(t_minist *minis);

void	handle_exit_with_code(t_minist *minis, long n);

void	handle_exit_non_num(t_minist *minis, char *str);

void	handle_exit_too_many_arg(t_minist *minis);

long	ft_atol_protecc(const char *s, int *error);

bool	ft_exit(t_minist *minis, char **str);

/* ************************************************************************** */
/* 																			  */
/* 									minibuilt_ins							  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief executes the correct built-in
 * 
 * @param s_minis 
 * @return int 
 */
bool	exec_built_ins(t_minist *minis, t_parser *parser_ptr, int which);

/**
 * @brief 
 * 
 * @param minis 
 * @param parser_ptr 
 * @param i 
 */
void	ft_free_built_ins(t_parser *parser_ptr);

bool	check_for_fork(t_parser *parser_ptr);

/**
 * @brief checks if there are built-ins and executes them
 * 
 * @param minis 
 * @return int 
 */
int		check_built_ins(t_minist *minis, t_parser *parser_ptr,
			t_check_built_in role);

#endif
