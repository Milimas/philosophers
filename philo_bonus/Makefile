CC = 			cc
CFLAGS = 		-Wall -Wextra -Werror -pthread
ADDRESS = 		-fsanitize=address -g
PTHREAD = 		-fsanitize=thread -g3
RM = 			rm -rf

NAME = 			philo_bonus

SRC_FILES = 	philosophers_bonus.c	\
				ft_atoi_bonus.c			\
				ft_putchar_bonus.c		\
				ft_putnbr_bonus.c		\
				ft_putstr_bonus.c		\
				help_bonus.c			\
				time_bonus.c			\
				birth_bonus.c			\
				check_bonus.c			\
				fork_bonus.c			\
				ft_itoa_bonus.c			\
				ft_strjoin_bonus.c		\

SRC_DIR = 		philo/

SRC = 			$(SRC_FILES)

OBJ = 			$(SRC:%.c=$(OBJ_DIR)%.o)

OBJ_DIR = 		obj/

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o:%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re