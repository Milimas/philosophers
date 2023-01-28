CC = 			cc
CFLAGS = 		-Wall -Wextra  -pthread
SANITIZE = 		-fsanitize=address -g
RM = 			rm -rf

NAME = 			philo

SRC_FILES = 	philosophers.c	\
				ft_atoi.c		\
				ft_putchar.c	\
				ft_putnbr.c		\
				ft_putstr.c		\
				help.c			\
				time.c			\
				birth.c			\
				check.c

SRC_DIR = 		philo/

SRC = 			$(SRC_FILES)

OBJ = 			$(SRC:%.c=$(OBJ_DIR)%.o)

OBJ_DIR = 		obj/

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o:%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re