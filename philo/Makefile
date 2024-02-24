# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momrane <momrane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 21:07:48 by momrane           #+#    #+#              #
#    Updated: 2024/02/24 11:48:49 by momrane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Variables
NAME 		=	philo
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread -g
HEADER		=	-I $(INC_DIR)

#Directories
SRC_DIR		=	./src
BIN_DIR 	=	./bin
INC_DIR 	=	./inc

# Colors
DEF_COLOR	= 	\033[0;39m
GREEN 		= 	\033[0;92m
CYAN 		= 	\033[0;96m

#Sources
SRC			=	$(SRC_DIR)/data_utils.c $(SRC_DIR)/data.c $(SRC_DIR)/destroy.c \
				$(SRC_DIR)/forks.c $(SRC_DIR)/free.c $(SRC_DIR)/main.c \
				$(SRC_DIR)/msg.c $(SRC_DIR)/mutex.c $(SRC_DIR)/philos.c $(SRC_DIR)/routine.c \
				$(SRC_DIR)/threads.c $(SRC_DIR)/time.c $(SRC_DIR)/utils.c

#Binaries
OBJ			= 	$(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

#Rules
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(HEADER) $(OBJ) -o $(NAME)
	@echo "$(GREEN)philo compiled!$(DEF_COLOR)"
			
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@rm -rf $(BIN_DIR)
	@echo "$(CYAN)binary files cleaned!$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(CYAN)exec files cleaned!$(DEF_COLOR)"

re: fclean $(NAME)
	@echo "$(GREEN)Cleaned and rebuilt everything for philo!$(DEF_COLOR)"

norm:
	@norminette $(SRC) $(INC_DIR)/*.h

.PHONY:	all clean fclean re norm