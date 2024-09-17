# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/18 11:52:19 by jlarieux          #+#    #+#              #
#    Updated: 2024/09/17 15:23:38 by jlarieux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC =	$(SRC_DIR)/ft_isalpha.c $(SRC_DIR)/ft_isdigit.c \
		$(SRC_DIR)/ft_isalnum.c $(SRC_DIR)/ft_isascii.c \
		$(SRC_DIR)/ft_isprint.c $(SRC_DIR)/ft_strlen.c \
		$(SRC_DIR)/ft_memset.c $(SRC_DIR)/ft_bzero.c $(SRC_DIR)/ft_memcpy.c \
		$(SRC_DIR)/ft_memmove.c $(SRC_DIR)/ft_strlcpy.c \
		$(SRC_DIR)/ft_strlcat.c $(SRC_DIR)/ft_toupper.c \
		$(SRC_DIR)/ft_tolower.c $(SRC_DIR)/ft_strchr.c \
		$(SRC_DIR)/ft_strlcpy.c $(SRC_DIR)/ft_strlcat.c \
		$(SRC_DIR)/ft_toupper.c $(SRC_DIR)/ft_tolower.c \
		$(SRC_DIR)/ft_strchr.c $(SRC_DIR)/ft_strrchr.c \
		$(SRC_DIR)/ft_strncmp.c $(SRC_DIR)/ft_memchr.c \
		$(SRC_DIR)/ft_memcmp.c $(SRC_DIR)/ft_strnstr.c \
		$(SRC_DIR)/ft_strrchr.c $(SRC_DIR)/ft_strncmp.c \
		$(SRC_DIR)/ft_memchr.c $(SRC_DIR)/ft_memcmp.c \
		$(SRC_DIR)/ft_strnstr.c $(SRC_DIR)/ft_atoi.c $(SRC_DIR)/ft_calloc.c \
		$(SRC_DIR)/ft_strdup.c $(SRC_DIR)/ft_substr.c \
		$(SRC_DIR)/ft_strjoin.c $(SRC_DIR)/ft_strtrim.c \
		$(SRC_DIR)/ft_split.c $(SRC_DIR)/ft_itoa.c $(SRC_DIR)/ft_strmapi.c \
		$(SRC_DIR)/ft_striteri.c $(SRC_DIR)/ft_putchar_fd.c \
		$(SRC_DIR)/ft_putstr_fd.c $(SRC_DIR)/ft_putendl_fd.c \
		$(SRC_DIR)/ft_putnbr_fd.c \
		$(SRC_DIR)/get_next_line_utils.c $(SRC_DIR)/get_next_line.c \
		$(SRC_DIR)/ft_lstnew.c $(SRC_DIR)/ft_lstadd_front.c \
		$(SRC_DIR)/ft_lstsize.c $(SRC_DIR)/ft_lstlast.c \
		$(SRC_DIR)/ft_lstadd_back.c $(SRC_DIR)/ft_lstclear.c \

SRC_DIR :=		src
OBJ_DIR :=		obj
BIN_DIR :=		.

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS :=	-Iinclude
CFLAGS :=	-Wall -Werror -Wextra -g

NAME = $(BIN_DIR)/libft.a

all : $(NAME)

$(NAME) : $(OBJ) | $(BIN_DIR)
	ar rcs $(NAME) $(OBJ)

$(BIN_DIR) ${OBJ_DIR} :
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) -rv $(OBJ_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re