# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: allblue <allblue@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 21:07:48 by momrane           #+#    #+#              #
#    Updated: 2024/02/10 15:21:07 by allblue          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Variables
NAME 		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread -g#remove -g before submit
HEADER		= -I $(INC_DIR)

#Directories
SRC_DIR		= ./src
BIN_DIR 	= ./bin
INC_DIR 	= ./inc

# Colors
DEF_COLOR	= \033[0;39m
GREEN 		= \033[0;92m
CYAN 		= \033[0;96m

#Sources
SRC_FILES 	= init main philos time free routine msg utils init2
SRC 		= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ			= $(addprefix $(BIN_DIR)/, $(addsuffix .o, $(SRC_FILES)))

ARGS		= 4 500 200 200 7

#Rules
all: $(NAME)

r: 
	./$(NAME) $(ARGS)

v:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

$(NAME): $(OBJ)
	@$(CC) $(HEADER) $(OBJ) -o $(NAME)
	@echo "$(GREEN)philo compiled!$(DEF_COLOR)"
			
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

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