# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 07:30:46 by edvicair          #+#    #+#              #
#    Updated: 2023/01/20 11:47:15 by edvicair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g
RL = -lreadline
INC = minishell.h
SRC = 	minishell.c \
		LIB/ft_free.c \
		LIB/lib.c \
		LIB/lib_bis.c \
		LIB/split.c \
		LIB/ft_atoi.c \
		INIT/init_env.c \
		INIT/init_tok.c \
		BUILT/cd.c \
		BUILT/pwd.c \
		BUILT/export.c \
		BUILT/export_sort.c \
		BUILT/env.c \
		BUILT/unset.c \
		BUILT/echo.c \
		BUILT/exit.c \
		PARSING/parsing.c \
		PARSING/tokenizator.c \
		PARSING/utils_parsing.c \
		PARSING/syntax.c \
		PARSING/utils_parsing2.c \
		EXEC/child.c \
		EXEC/redir.c \
		EXEC/exec.c \
		INIT/init_redir.c
OBJ=$(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME) $(CFLAGS) $(RL) #-fsanitize=address
	
%.o: %.c
	gcc -g -o $@ -c $< 

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all
