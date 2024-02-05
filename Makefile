# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: allblue <allblue@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 21:07:48 by momrane           #+#    #+#              #
#    Updated: 2024/02/05 16:29:34 by allblue          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Variables
NAME 		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
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
SRC_FILES 	= main ft_atoi ft_check_args philos utils env actions time
SRC 		= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ			= $(addprefix $(BIN_DIR)/, $(addsuffix .o, $(SRC_FILES)))

ARGS		= 2 800 200 200 200

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