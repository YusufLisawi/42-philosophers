NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g

SRCS = main.c utilities.c utils.c checks.c 

OBJS = $(SRCS:c=o)

all: $(NAME) 

$(NAME): $(OBJS) philo.h
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re 