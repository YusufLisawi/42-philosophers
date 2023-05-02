NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

SRCS = main.c utilities.c utils.c 

OBJS = $(SRCS:c=o)

all: $(NAME) 

$(NAME): $(OBJS) philo.h
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all bonus clean fclean re 