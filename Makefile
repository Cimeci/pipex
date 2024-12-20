# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 10:50:48 by inowak--          #+#    #+#              #
#    Updated: 2024/12/20 09:44:38 by inowak--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color #

CYAN     = \033[1;36m
WHITE    = \033[1;37m
BLACK    = \033[1;30m
ORANGE   = \033[38;5;202m  # Couleur spécifique (non standard)
GRAY     = \033[1;90m
LIGHT_RED = \033[1;91m
LIGHT_GREEN = \033[1;92m
LIGHT_YELLOW = \033[1;93m
LIGHT_BLUE = \033[1;94m
LIGHT_PURPLE = \033[1;95m
LIGHT_CYAN = \033[1;96m
LIGHT_WHITE = \033[1;97m
RED    = \033[1;31m
GREEN  = \033[1;32m
YELLOW = \033[1;33m
BLUE   = \033[1;34m
PURPLE = \033[1;35m
RESET  = \033[0m

NAME = pipex
BONUS = double_pipex

CC = cc
CFLAGS := -Wall -Wextra -Werror -g

PRINTF_FILES = lib/ft_printf/ft_pointer.c\
				lib/ft_printf/ft_put.c\
				lib/ft_printf/ft_printf_handle.c\
				lib/ft_printf/ft_printf.c\

GNL_FILES = lib/gnl/get_next_line_utils.c\
			lib/gnl/get_next_line.c\

LIBFT_DIR = lib/libft

SRC = mandatory/ft_clean.c\
		mandatory/ft_parsing.c\
		mandatory/ft_init.c\
		mandatory/ft_process.c\
		mandatory/ft_find_path.c\
		mandatory/main.c


SRC_BONUS = bonus/ft_clean_bonus.c\
		bonus/ft_parsing_bonus.c\
		bonus/ft_init_bonus.c\
		bonus/ft_process_bonus.c\
		bonus/ft_find_path_bonus.c\
		bonus/main_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_LIB = $(PRINTF_FILES:.c=.o) $(GNL_FILES:.c=.o)
OBJ_LIBFT = $(LIBFT_DIR)/libft.a
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(OBJ_LIBFT):
	@cd $(LIBFT_DIR) && make > /dev/null

bonus : $(BONUS)

$(NAME): $(OBJ) $(OBJ_LIB) $(OBJ_LIBFT)
	@$(CC) $(OBJ) $(OBJ_LIB) $(OBJ_LIBFT) -L$(LIBFT_DIR) -I$(LIBFT_DIR) -o $(NAME)
	@echo "$(ORANGE)";
	@echo " ######    ####    ######   #######  ##  ##";
	@echo "  ##  ##    ##      ##  ##   ##   #  ##  ##";
	@echo "  ##  ##    ##      ##  ##   ## #     ####";
	@echo "  #####     ##      #####    ####      ##";
	@echo "  ##        ##      ##       ## #     ####";
	@echo "  ##        ##      ##       ##   #  ##  ##";
	@echo " ####      ####    ####     #######  ##  ##";
	@echo "$(RESET)";

$(BONUS): $(OBJ_BONUS) $(OBJ_LIB) $(OBJ_LIBFT)
	@$(CC) $(OBJ_LIB) $(OBJ_BONUS) $(OBJ_LIBFT) -L$(LIBFT_DIR) -I$(LIBFT_DIR) -o $(NAME)
	@echo "$(LIGHT_CYAN)"
	@echo " ######    #####   ##   ##  ##   ##   #####"
	@echo "  ##  ##  ##   ##  ###  ##  ##   ##  ##   ##"
	@echo "  ##  ##  ##   ##  #### ##  ##   ##  #"
	@echo "  #####   ##   ##  ## ####  ##   ##   #####"
	@echo "  ##  ##  ##   ##  ##  ###  ##   ##       ##"
	@echo "  ##  ##  ##   ##  ##   ##  ##   ##  ##   ##"
	@echo " ######    #####   ##   ##   #####    #####"
	@echo "$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@echo "$(RED)clean$(RESET)"
	@$(MAKE) clean -C $(LIBFT_DIR) > /dev/null
	@rm -f $(OBJ) $(OBJ_LIB) $(OBJ_BONUS)

fclean: clean
	@echo "$(YELLOW)remove$(YELLOW) $(RED)$(NAME)$(RESET)"
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null
	@rm -f $(NAME)
	@rm -f $(BONUS)

re: fclean all
	@echo "$(NAME) restart"

.PHONY: all clean fclean re bonus
