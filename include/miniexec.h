/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:05:43 by mlarieux          #+#    #+#             */
/*   Updated: 2025/04/07 23:56:14 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIEXEC_H
# define MINIEXEC_H

typedef enum e_cmd
{
	CMD_FIRST = 0,
	CMD_INTER = 1,
	CMD_LAST = 2
}	t_cmd;

typedef struct s_minist	t_minist;

typedef struct s_exec
{
	int	eof_len;
	int	last_cmd;
	int	fd_pipe[2];
	int	fd_in;
	int	fd_out;
	int	fd_prev_out;
}		t_exec;

/* ************************************************************************** */
/* 																			  */
/* 									pipex_utils								  */
/* 																			  */
/* ************************************************************************** */

void	check_here_doc(t_minist *minis);

/**
 * @brief initializes fds and checks for here_doc
 * 
 * @param minis 
 * @return int 
 */
int		init_pipex(t_minist *minis);

/**
 * @brief waits each pid saved in a linked list
 * 
 * @param s_p 
 */
int		wait_each_pid(t_minist *s_minis);

/* ************************************************************************** */
/* 																			  */
/* 									pipex_errors.c							  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief exits in case of fd error
 * 
 */
void	fd_error(t_minist *minis, char *str);

/**
 * @brief frees stuff, writes the error and exits in case of execve error
 * 
 * @param dtab 
 * @param dtab2 
 * @param tab 
 */
void	mini_execve_error(char **dtab, char **dtab2, char *tab);

/* ************************************************************************** */
/* 																			  */
/* 									pipex_here_doc							  */
/* 																			  */
/* ************************************************************************** */

void	exec_heredoc(t_minist *minis, t_inout *io, char **line);

/**
 * @brief initiates heredoc
 * 
 * @param limiter 
 */
void	init_heredoc(t_minist *s_minis, t_inout *io);

/* ************************************************************************** */
/* 																			  */
/* 									pipex_args_utils						  */
/* 																			  */
/* ************************************************************************** */

char	**strdup_cmd(t_minist *minis, char **exp_value);

/* ************************************************************************** */
/* 																			  */
/* 									pipex_args_van_cmd						  */
/* 																			  */
/* ************************************************************************** */

void	join_van_cmd(t_minist *minis,
			char **cmd, char **van_cmd_args, int *i);

char	*set_van_cmd_args(t_minist *minis, char **cmd);

/**
 * @brief in case find_cmd doesn't work, attempts to check if the cmd is in 
 * absolute path form and executes it
 * 
 * @param s_p 
 * @param cmd 
 */
void	exec_vanilla_cmd(t_minist *minis, char **env, char **cmd);

/* ************************************************************************** */
/* 																			  */
/* 									pipex_args								  */
/* 																			  */
/* ************************************************************************** */

/** 
 * @brief finds the paths in envp and returns them in a double array
 * 
 * @param s_p 
 * @return char** 
 */
char	**find_paths(char **env);

char	*exec_cmd(t_minist *minis, char **paths, char **cmd);

/**
 * @brief attempts to execve the current command by giving the command and it's
 * args in a double array and it's path in an array
 * 
 * @param s_p 
 * @param cmd 
 */
void	find_cmd(t_minist *s_minis, char **cmd);

/* ************************************************************************** */
/* 																			  */
/* 								pipex_dup_and_close							  */
/* 																			  */
/* ************************************************************************** */

int		dup_and_close_pipes(t_minist *minis, int role);

int		dup_and_close_redir(t_minist *minis, int role);

/* ************************************************************************** */
/* 																			  */
/* 								pipex_manage_children						  */
/* 																			  */
/* ************************************************************************** */

void	manage_child_first(t_minist *minis);

void	manage_child_last(t_minist *minis);

void	manage_child_inter(t_minist *minis);

/**
 * @brief dups and closes the rights fds and stuff, in accordance with which
 * command it is
 * 
 * @param fd 
 * @param fd_pipe 
 * @param childno 
 */
void	dup_and_close(t_minist *s_minis, t_cmd childno);

void	child_error(t_minist *minis, t_parser *oparser_ptr);

/* ************************************************************************** */
/* 																			  */
/* 								pipex_children_utilities					  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief executes the open function with the right parameters
 * 
 * @param str 
 * @param role 
 * @return int 
 */
int		open_out(char *str, int role);

void	open_io(t_minist *minis, t_inout *io_ptr, int role);

void	check_for_io(t_minist *minis, t_parser *parser_ptr);

void	close_unused(t_minist *minis, int role);

void	check_fd(int fd1, int fd2, int fd3, int fd4);

/* ************************************************************************** */
/* 																			  */
/* 									pipex_children							  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief opens the outfile and then calls dup_and_close and find_cmd,
 * giving them the fds and the splitted current command
 * 
 * @param s_p 
 * @param fd_pipe 
 */
void	child(t_minist *minis, t_parser *parser_ptr);

/**
 * @brief dups and closes the fd from where we are in the pipeline and calls
 * find_cmd, giving it the splitted current command
 * 
 * @param s_p
 * @param fd_pipe 
 */
void	inter_child(t_minist *minis, t_parser *parser_ptr);

/**
 * @brief opens the infile and then calls dup_and_close and find_cmd,
 * giving them the fds and the splitted current command
 * 
 * @param s_p 
 * @param fd_pipe 
 */
void	child2(t_minist *minis, t_parser *parser_ptr);

/* ************************************************************************** */
/* 																			  */
/* 									pipex_exec								  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief 
 * 
 * @param minis 
 * @param role 
 */
void	children(t_minist *minis, t_parser *parser_ptr, t_cmd role);

/**
 * @brief 
 * 
 * @param minis 
 * @param role 
 */
void	parent(t_minist *minis, t_cmd role);

/**
 * @brief forks then if it's the child calls the correct child and if it's
 * the parent, closes the corredt fds and saves the pid in the linked list
 * 
 * @param s_p 
 * @param fd_pipe 
 */
void	do_fork(t_minist *minis, t_parser *parser_ptr, t_cmd role);

/**
 * @brief executes pipe, the fd saved in an int* given to it and if it doesn't
 * work exits
 * 
 * @param fd_pipe 
 */
void	do_pipe(t_minist *minis);

/**
 * @brief for each command, calls do_pipe and do_child with the correct
 * arguments according to which is the current command
 * 
 * @param s_p 
 * @param argc 
 */
void	do_pipex(t_minist *minis, t_parser *parser_ptr);

/* ************************************************************************** */
/* 																			  */
/* 									pipex									  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief executes the given commands with their args in the given order and
 * gives to each command the correct input and output according to where it
 * is in the pipeline, each command recieves the output of the previous ones
 * and the first and last commands read the infile and write in the outfile
 * respectively
 * 
 * @param argc 
 * @param argv 
 * @param envp 
 * @return int 
 */
int		pipex(t_minist *s_minis);

#endif
