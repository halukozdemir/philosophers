NAME = philo
SRC = argv_checker.c close.c eating.c init.c main.c mutex_utils.c philosophers.c solo_philo.c time_utils.c utils.c
OBJ := $(SRC:.c=.o)
CFLAGS = -fsanitize=thread -Wall -Wextra -Werror
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
