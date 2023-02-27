CC = 			cc
CFLAGS = 		-Wall -Wextra -Werror -pthread
ADDRESS = 		-fsanitize=address -g
PTHREAD = 		-fsanitize=thread -g3
RM = 			rm -rf

NAME = 			philo_bonus

SRC_FILES =	ph_action_bonus.c	\
			ph_atoi_bonus.c		\
			ph_check_bonus.c	\
			ph_fork_bonus.c		\
			ph_init_bonus.c		\
			ph_main_bonus.c		\
			ph_philo_bonus.c	\
			ph_print_bonus.c	\
			ph_time_bonus.c		\
			ph_destroy_bonus.c	\
			ph_wait_bonus.c


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