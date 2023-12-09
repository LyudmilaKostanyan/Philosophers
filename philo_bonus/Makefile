NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread
FILES_DIR = ./src
OBJ_DIR = ./obj
FILES = $(addprefix $(FILES_DIR)/, die.c init.c main.c mini_libft.c parse.c utils.c)
OBJ = $(patsubst $(FILES_DIR)/%.c, $(OBJ_DIR)/%.o, $(FILES))

$(OBJ_DIR)/%.o: $(FILES_DIR)/%.c Makefile $(FILES_DIR)/philo.h
	$(CC) $(FLAGS) -c $< -o $@

all: mkdir $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

mkdir:
	@mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ)
	rm -fd $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re