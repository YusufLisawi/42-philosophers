NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c philo_utils.c utils.c 

OBJS = $(SRCS:c=o)

all: $(NAME) 

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all bonus clean fclean re 