# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 14:09:46 by mlarieux          #+#    #+#              #
#    Updated: 2025/01/16 13:04:19 by mlarieux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### sources ###
SRC_EXEC =		pipex_utilities.c \
				pipex_errors.c \
				pipex_dup_and_close.c \
				pipex_manage_children.c \
				pipex_children_utilities.c \
				pipex_heredoc.c \
				pipex_args_utils.c \
				pipex_args_van_cmd.c \
				pipex_args.c \
				pipex_children.c \
				pipex_exec.c \
				pipex.c 
SRC_BUILT_INS =	minibuilt_ins_actions_utils.c \
				minibuilt_ins_actions.c \
				minibuilt_ins_ctrl_utils.c \
				minibuilt_ins_ctrl.c \
				minibuilt_ins_exit.c \
				minibuilt_ins.c \
				ft_miniatol.c
SRC_PARSER =	miniparser_utils.c \
				minitokens_utils.c \
				minitokens_recursive_len.c \
				minitokens_len.c \
				minitokens_quotes.c \
				minitokens_vars_utils.c \
				minitokens_vars_setfind.c \
				minitokens_vars.c \
				minitokens_data.c \
				minitokens.c \
				miniparser_translate.c \
				miniparser_translate_utils.c \
				miniparser.c
SRC_MAIN =		minierrors_set_show.c \
				minierrors.c \
				miniinit.c \
				minisignals.c \
				miniutils.c \
				minifrees.c \
				minishell.c 

### directories ###
SRC_DIR			:= src
MAIN_DIR		:= main
EXEC_DIR		:= exec
BUILT_INS_DIR	:= built_ins
PARSER_DIR		:= parser
OBJ_DIR			:= obj
LIBFT_DIR		:= $(SRC_DIR)/libft
BIN_DIR			:= .

VPATH = $(SRC_DIR)/$(EXEC_DIR) $(SRC_DIR)/$(BUILT_INS_DIR) \
		$(SRC_DIR)/$(PARSER_DIR) \
		$(SRC_DIR)/$(MAIN_DIR) 

### objects ###
SRC = $(SRC_EXEC) $(SRC_BUILT_INS) $(SRC_PARSER) $(SRC_MAIN)

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

### flags ###
CPPFLAGS :=	-Iinclude -I$(LIBFT_DIR)/include
CFLAGS :=	-Wall -Werror -Wextra -g
LDFLAGS :=	-L$(LIBFT_DIR)
LDLIBS :=	-lm -lreadline

LIBFT = $(LIBFT_DIR)/libft.a

NAME = $(BIN_DIR)/minishell

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ $(LIBFT)

$(BIN_DIR) ${OBJ_DIR} :
	mkdir -p $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

clean :
	$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) -rv $(OBJ_DIR)

fclean : clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re : fclean all

supp :
	valgrind --leak-check=full --gen-suppressions=all $(NAME)

minigrind :
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp $(NAME)

gdb :
	valgrind --leak-check=full --suppressions=readline.supp --vgdb=yes --vgdb-error=0 $(NAME)

.PHONY : all $(LIBFT) clean fclean re supp minigrind gdb
