NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
FILES_DIR = ./mandatory
OBJS_DIR = ./objs
FILES = $(wildcard $(FILES_DIR)/*.c)
OBJS = $(patsubst $(FILES_DIR)/%.c, $(OBJS_DIR)/%.o, $(FILES))

$(OBJS_DIR)/%.o: $(FILES_DIR)/%.c Makefile
	$(CC) $(FLAGS) -c $< -o $@

all: mkdir $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

mkdir:
	@mkdir -p $(OBJS_DIR)

clean: 
	rm -f $(OBJS)
	rm -fd $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re