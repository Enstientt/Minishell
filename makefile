# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/25 11:15:10 by ahammout          #+#    #+#              #
#    Updated: 2023/02/18 16:14:51 by ahammout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

#CFLAGS = -Wall -Wextra -Werror -g

READLINEFLAG =   -lreadline

LIBFT = libft/libft.a

INCLUDES = includes/minishell.h

NAME = minishell

SRCS = 	srcs/main.c \
		srcs/parsing/utils.c \
		srcs/parsing/parse_line.c \
		srcs/parsing/lexer/lexer.c \
		srcs/parsing/lexer/lexer_check_tools.c \
		srcs/parsing/lexer/lexer_tools.c \
		srcs/parsing/lexer/lexer_quotes.c \
		srcs/parsing/environment/set_environment.c \
		srcs/parsing/environment/sort_environemnt.c \
		srcs/parsing/syntax_analyzer/syntax_analyzer.c \
		srcs/parsing/syntax_analyzer/syntax_analyzer_.c \
		srcs/parsing/syntax_analyzer/syntax_quotes.c \
		srcs/parsing/expander/expander.c \
		srcs/parsing/expander/expandable.c \
		srcs/parsing/expander/unexpandable.c \
		srcs/execution/built_in_cmd.c \
		srcs/execution/export.c \
		srcs/execution/unset.c \
		srcs/execution/pipex.c \
		srcs/execution/pipex_extra.c \
		srcs/execution/pwd.c \
		srcs/execution/signal_handler.c \
		srcs/execution/exit.c \
		srcs/execution/cmd_exec.c \
		srcs/execution/echo.c \
		srcs/execution/cd.c \

OBJS = $(SRCS:.c=.o)

%.o : %.c $(INCLUDES) -lreadline
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS) $(INCLUDES)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINEFLAG) -o $(NAME)

clean :
	@make clean -C libft
	@rm -rf $(OBJS)

fclean : clean
	@make fclean -C libft
	@rm -rf $(NAME)

re : fclean all
