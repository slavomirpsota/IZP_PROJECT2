NAME=main
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror -pedantic

$(NAME): $(NAME).c
	$(CC) $(CFLAGS) $(NAME).c -lm -o $(NAME)

clean:
	rm -f $(NAME) output
