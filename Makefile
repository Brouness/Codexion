NAME = codexion
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g

SRC = src/cleanup.c\
		src/coder.c\
		src/dongle.c\
		src/heap.c\
		src/init.c\
		src/logger.c\
		src/main.c\
		src/monitor.c\
		src/parsing.c\
		src/utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c codexion.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: clean