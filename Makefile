# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 01:15:26 by abeihaqi          #+#    #+#              #
#    Updated: 2023/02/27 01:15:27 by abeihaqi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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