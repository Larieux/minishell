/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:14:27 by jlarieux          #+#    #+#             */
/*   Updated: 2024/10/01 14:54:54 by jlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef READ
#  define READ	0
# endif
# ifndef WRITE
#  define WRITE	1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>//
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "minishell.h"
# include "../src/libft/include/libft.h"

typedef struct s_miniargs
{
	char				*value;
	int					quotes;
	struct s_miniargs	*next;
}				t_miniargs;

typedef struct s_minicmd
{
	char				*value;
	int					input;
	int					output;
	struct s_miniargs	args;
	struct s_minicmd	*next;
}				t_minicmd;

typedef struct s_miniinfiles
{
	char					*value;
	struct s_miniinfiles	*next;
}							t_miniinfiles;

typedef struct s_minioutfiles
{
	char					*value;
	struct s_minioutfiles	*next;
}							t_minioutfiles;

typedef struct s_minist
{
	char			**args;
	char			**env;
	const char		*built_ins_ptr;
	char			*infile;
	char			*outfile;
	int				arg_c_or;
	int				arg_c;
	int				first_cmd;
	int				eof_len;
	int				here_doc;
	t_minicmd		*cmds;
	t_miniinfiles	*infiles;
	t_minioutfiles	*outfiles;
	t_list			*pid_lst;
}					t_minist;

/* ************************************************************************** */
/* 																			  */
/* 									pipex_utils								  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief executes the open function with the right parameters
 * 
 * @param str 
 * @param role 
 * @return int 
 */
int		ft_exec_open(char *str, int role);

/**
 * @brief frees a double array
 * 
 * @param tab 
 */
void	free_dtab(char **tab);

/**
 * @brief exits in case of malloc error
 * 
 * @param dtab 
 */
void	exit_malloc(char **dtab);

/**
 * @brief frees a double tab and exits in case of malloc error
 * 
 * @param tab 
 */
void	exit_dfree_malloc(char **tab);

/**
 * @brief exits in case of fd error
 * 
 */
void	fd_error(char *str);

/* ************************************************************************** */
/* 																			  */
/* 									pipex_here_doc							  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief executes the write and read (GNL) part of heredoc
 * 
 * @param line 
 * @param fd 
 * @param line_len 
 */
void	exec_heredoc(char **line, int *fd, int *line_len);

/**
 * @brief initiates heredoc
 * 
 * @param limiter 
 */
void	init_heredoc(t_minist *s_minis);

/* ************************************************************************** */
/* 																			  */
/* 									pipex_args								  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief checks for the number of args and if the first one is here_doc,
 * executes here_doc if so
 * 
 * @param argc 
 * @param s_p 
 * @param envp 
 * @return int 
 */
int		errors(int argc, t_minist *s_minis, char **envp);

/**
 * @brief finds the paths in envp and returns them in a double array
 * 
 * @param s_p 
 * @return char** 
 */
char	**find_paths(t_minist *s_minis);

/**
 * @brief in case find_cmd doesn't work, attempts to check if the cmd is in 
 * absolute path form and executes it
 * 
 * @param s_p 
 * @param cmd 
 */
void	exec_vanilla_cmd(t_minist *s_minis, char **cmd);

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
/* 								pipex_children_management					  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief Construct a new ft lst pid object
 * 
 * @param s_p 
 * @param pid 
 */
void	lst_pid(t_minist *s_minis, pid_t pid);

/**
 * @brief dups and closes the rights fds and stuff, in accordance with which
 * command it is
 * 
 * @param fd 
 * @param fd_pipe 
 * @param childno 
 */
void	dup_and_close(int fd, int *fd_pipe, int prev_fd, int childno);

/**
 * @brief frees stuff, writes the error and exits in case of execve error
 * 
 * @param dtab 
 * @param dtab2 
 * @param tab 
 */
void	execve_error(t_minist *s_minis, char **dtab, char **dtab2, char *tab);

/* ************************************************************************** */
/* 																			  */
/* 									minibuilt_ins_actions_utils				  */
/* 																			  */
/* ************************************************************************** */

/* ************************************************************************** */
/* 																			  */
/* 									minibuilt_ins_actions					  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief writes in the stdout the arguments given to it
 * 
 * @param str 
 * @return int 
 */
int		ft_echo(char *str, bool n);

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
int		exec_built_ins(t_minist *s_minis);

/**
 * @brief checks which built-in to give to exec_built_ins through an indicator
 * 
 * @param s_minis 
 * @return int 
 */
int		check_built_ins(t_minist *s_minis);

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
void	child(t_minist *s_minis, int *fd_pipe);

/**
 * @brief dups and closes the fd from where we are in the pipeline and calls
 * find_cmd, giving it the splitted current command
 * 
 * @param s_p 
 * @param fd_pipe 
 */
void	inter_child(t_minist *s_minis, int *fd_pipe, int prev_fd);

/**
 * @brief opens the infile and then calls dup_and_close and find_cmd,
 * giving them the fds and the splitted current command
 * 
 * @param s_p 
 * @param fd_pipe 
 */
void	child2(t_minist *s_minis, int *fd_pipe, int prev_fd);

/* ************************************************************************** */
/* 																			  */
/* 									pipex_exec								  */
/* 																			  */
/* ************************************************************************** */

/**
 * @brief waits each pid saved in a linked list
 * 
 * @param s_p 
 */
int		wait_each_pid(t_minist *s_minis);

/**
 * @brief forks then if it's the child calls the correct child and if it's
 * the parent, closes the corredt fds and saves the pid in the linked list
 * 
 * @param s_p 
 * @param fd_pipe 
 */
void	do_fork(t_minist *s_minis, int *fd_pipe, int prev_fd, int role);

/**
 * @brief executes pipe, the fd saved in an int* given to it and if it doesn't
 * work exits
 * 
 * @param fd_pipe 
 */
void	do_pipe(int *fd_pipe);

/**
 * @brief for each command, calls do_pipe and do_child with the correct
 * arguments according to which is the current command
 * 
 * @param s_p 
 * @param argc 
 */
void	do_pipex(t_minist *s_minis, int argc);

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