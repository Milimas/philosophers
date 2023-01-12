CC = 			cc
CFLAGS = 		-Wall -Wextra  -pthread
SANITIZE = 		-fsanitize=address -g
RM = 			rm -rf

NAME = 			philosophers
BNAME = 		philosophers_bonus

SRC_FILES = 	philosophers.c	\
				ft_atoi.c		\
				ft_putchar.c	\
				ft_putnbr.c	\
				ft_putstr.c		

BSRC_FILES =	philosophers_bonus.c

SRC_DIR = 		philo/
BSRC_DIR = 		philo_bonus/

SRC = 			$(addprefix $(SRC_DIR), $(SRC_FILES))
BSRC = 			$(addprefix $(BSRC_DIR), $(BSRC_FILES))

OBJ = 			$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
BOBJ = 			$(BSRC:$(BSRC_DIR)%.c=$(BOBJ_DIR)%.o)

OBJ_DIR = 		$(SRC_DIR)obj/
BOBJ_DIR = 		$(BSRC_DIR)obj/

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(SANITIZE)

$(BNAME): $(BOBJ)
	$(CC) $(CFLAGS) $(BOBJ) -o $(BNAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BOBJ_DIR)%.o:$(BSRC_DIR)%.c
	mkdir -p $(BOBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME) bonus

bonus: $(BNAME)

clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(BOBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BNAME)

re: fclean all

.PHONY: bonus all clean fclean re