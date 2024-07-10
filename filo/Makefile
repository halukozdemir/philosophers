NAME = philo
SRC = philo.c argv_checker.c utils.c
OBJ := $(SRC:.c=.o)
CFLAGS = # -fsanitize=thread -Wall -Wextra -Werror
CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
