NAME = philo
BNAME = philo_bonus

SRC_DIR = 		philo/
BSRC_DIR = 		philo_bonus/

OBJ_DIR = 		$(SRC_DIR)obj/
BOBJ_DIR = 		$(BSRC_DIR)obj/

$(NAME):
	$(MAKE) -C $(SRC_DIR)

$(BNAME):
	$(MAKE) -C $(BSRC_DIR)

all: $(NAME) bonus

bonus: $(BNAME)

clean:
	$(MAKE) -C $(SRC_DIR) clean
	$(MAKE) -C $(BSRC_DIR) clean

fclean:
	$(MAKE) -C $(SRC_DIR) fclean
	$(MAKE) -C $(BSRC_DIR) fclean

re: fclean all

.PHONY: bonus all clean fclean re philo philo_bonus