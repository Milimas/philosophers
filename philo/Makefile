# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 01:15:37 by abeihaqi          #+#    #+#              #
#    Updated: 2023/03/13 20:43:12 by abeihaqi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = 			cc
CFLAGS = 		-Wall -Wextra -Werror -pthread -O3
ADDRESS = 		-fsanitize=address -g
PTHREAD = 		-fsanitize=thread -g3
RM = 			rm -rf

NAME = 			philo

SRC_FILES =	ph_action.c		\
			ph_atoi.c		\
			ph_check.c		\
			ph_fork.c		\
			ph_init.c		\
			ph_main.c		\
			ph_philo.c		\
			ph_print.c		\
			ph_time.c		\
			ph_destroy.c


SRC_DIR = 		philo/

SRC = 			$(SRC_FILES)

OBJ = 			$(SRC:%.c=$(OBJ_DIR)%.o)

OBJ_DIR = 		obj/

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

debug: 
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(PTHREAD)

$(OBJ_DIR)%.o:%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re debug