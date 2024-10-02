# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 14:09:46 by jlarieux          #+#    #+#              #
#    Updated: 2024/10/02 08:29:28 by jlarieux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	$(SRC_DIR)/minibuilt_ins_actions.c $(SRC_DIR)/minibuilt_ins_ctrl.c \
		$(SRC_DIR)/minibuilt_ins.c \
		$(SRC_DIR)/minishell.c \
		\
		$(SRC_DIR)/pipex_children_managment.c $(SRC_DIR)/pipex_utilities.c \
		$(SRC_DIR)/pipex_heredoc.c $(SRC_DIR)/pipex_args.c \
		$(SRC_DIR)/pipex_children.c $(SRC_DIR)/pipex_exec.c \
		$(SRC_DIR)/pipex.c \

SRC_DIR :=		src
OBJ_DIR :=		obj
LIBFT_DIR :=	$(SRC_DIR)/libft
BIN_DIR :=		.

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS :=	-Iinclude
CFLAGS :=	-Wall -Werror -Wextra -g
LDFLAGS :=	-L$(LIBFT_DIR)
LDLIBS :=	-lm

LIBFT = $(LIBFT_DIR)/libft.a

NAME = $(BIN_DIR)/minishell

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ $(LIBFT)

$(BIN_DIR) ${OBJ_DIR} :
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
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

.PHONY : all $(LIBFT) clean fclean re