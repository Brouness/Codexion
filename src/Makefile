NAME = codexion
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g

SRC = cleanup.c\
		coder.c\
		dongle.c\
		heap.c\
		init.c\
		logger.c\
		main.c\
		monitor.c\
		parsing.c\
		time_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c push_swap.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: clean