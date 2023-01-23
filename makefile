# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/25 11:15:10 by ahammout          #+#    #+#              #
#    Updated: 2023/01/15 17:59:20 by ahammout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

READLINEFLAG =   -lreadline -lhistory

LIBFT = libft/libft.a

LIB = minishell.h

NAME = minishell

SRCS = 	main.c \
		utils.c \
		lexer.c \
		lexer_.c \
		lexer_utils.c \
		syntax_checker.c \
		syntax_checker_.c \
		quotes.c \
		expander.c \
		exp_silent.c \
		exp_variable.c \

OBJS = $(SRCS:.c=.o)

%.o : %.c $(LIB) -lreadline
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)
$(NAME) : $(OBJS) $(LIB)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINEFLAG)  -o $(NAME)

clean :
	@make clean -C libft
	@rm -rf $(OBJS)


fclean : clean
	@make fclean -C libft
	@rm -rf $(NAME)

re : fclean all
