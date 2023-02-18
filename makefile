# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/25 11:15:10 by ahammout          #+#    #+#              #
#    Updated: 2023/02/18 14:20:41 by ahammout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

READLINEFLAG =   -lreadline -lhistory

LIBFT = libft/libft.a

LIB = includes/minishell.h

NAME = minishell

SRCS = 	srcs/main.c \
		srcs/parsing/utils.c \
		srcs/parsing/parse_line.c \
		srcs/parsing/lexer/lexer.c \
		srcs/parsing/lexer/lexer_check_tools.c \
		srcs/parsing/lexer/lexer_tools.c \
		srcs/parsing/lexer/lexer_quotes.c \
		srcs/parsing/syntax_analyzer/syntax_analyzer.c \
		srcs/parsing/syntax_analyzer/syntax_analyzer_.c \
		srcs/parsing/syntax_analyzer/syntax_quotes.c \
		srcs/parsing/expander/expander.c \
		srcs/parsing/expander/expandable.c \
		srcs/parsing/expander/unexpandable.c \

OBJS = $(SRCS:.c=.o)

%.o : %.c $(LIB) -lreadline
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS) $(LIB)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINEFLAG) -o $(NAME)

clean :
	@make clean -C libft
	@rm -rf $(OBJS)

fclean : clean
	@make fclean -C libft
	@rm -rf $(NAME)

re : fclean all
