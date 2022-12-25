# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammout <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/25 11:15:10 by ahammout          #+#    #+#              #
#    Updated: 2022/12/25 11:15:15 by ahammout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

READLINEFLAG = -lreadline

LIBFT = libft/libft.a

LIB = minishell.h

NAME = minishell

SRCS = 	main.c \
		utils.c \
		lexer.c \
		lexer_utils.c \

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
