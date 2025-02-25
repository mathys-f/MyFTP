##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile for program compilation
##

.PHONY: all clean fclean re unit_tests tests_run

NAME = myftp

SRC	=

TEST_FILES = tests/tests_myftp.c

OBJ	= $(SRC:.c=.o)

CC = gcc -g

CFLAGS = -std=gnu17 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) main.c

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f *.gcda
	rm -f *.gcno
	rm -f unit_tests

re: fclean all

unit_tests: fclean
	$(CC) -o unit_tests $(SRC) $(TEST_FILES) \
	--coverage -lcriterion -I ./include

tests_run: unit_tests
	./unit_tests
	gcovr --exclude tests/
