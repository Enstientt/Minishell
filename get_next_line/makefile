CC = gcc -c

FLAGS = -Wall -Wextra -Werror

ARCHC = ar rc

NAME = get_next_line.a

LIB = get_next_line.h

SRCS = get_next_line.c	\
	   get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIB)
	@$(CC) $(SRCS)
	@$(ARCHC) $(NAME) $(OBJS)

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

