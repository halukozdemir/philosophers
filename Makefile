NAME = philo
SRC = init.c main.c utils.c routine.c actions.c cleanup.c
OBJ := $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
