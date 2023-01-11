# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/25 11:15:10 by ahammout          #+#    #+#              #
#    Updated: 2023/01/10 19:01:50 by ahammout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

READLINEFLAG = -lreadline

LIBFT = libft/libft.a

LIB = minishell.h

NAME = minishell

SRCS = 	main.c \
		minishell.c \
		utils.c \
		lexer.c \
		lexer_.c \
		lexer_utils.c \
		syntax_checker.c \
		syntax_checker_.c \
		quotes.c \
		expander.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIB)
	@make -C libft
	@$(CC) $(CFLAGS) $(LIBFT) $(READLINEFLAG) $(OBJS) -o $(NAME)

clean :
	@make clean -C libft
	@rm -rf $(OBJS)


fclean : clean
	@make fclean -C libft
	@rm -rf $(NAME)

re : fclean all
