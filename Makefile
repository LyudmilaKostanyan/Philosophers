NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
FILES = main.c \
		parse.c
OBJS = $(FILES:.c=.o)

%.o: %.c Makefile
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re