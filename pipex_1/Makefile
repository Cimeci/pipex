# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 10:50:48 by inowak--          #+#    #+#              #
#    Updated: 2024/12/10 14:46:51 by inowak--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color #

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

LIBFT_FILES = lib/libft/ft_split.c\
				lib/libft/ft_strncmp.c\

SRC = 

SRC_MAIN = mandatory/main.c\

SRC_BONUS = 

OBJ = $(SRC:.c=.o)
OBJ_MAIN = $(SRC_MAIN:.c=.o)
OBJ_LIB = $(PRINTF_FILES:.c=.o) $(GNL_FILES:.c=.o) $(LIBFT_FILES:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

bonus : $(BONUS)

$(NAME): $(OBJ) $(OBJ_LIB) $(OBJ_MAIN)
	@$(CC) $(OBJ) $(OBJ_MAIN) $(OBJ_LIB) -o $(NAME)
	@echo "$(PURPLE)";
	@echo " ######    ####    ######   #######  ##  ##";
	@echo "  ##  ##    ##      ##  ##   ##   #  ##  ##";
	@echo "  ##  ##    ##      ##  ##   ## #     ####";
	@echo "  #####     ##      #####    ####      ##";
	@echo "  ##        ##      ##       ## #     ####";
	@echo "  ##        ##      ##       ##   #  ##  ##";
	@echo " ####      ####    ####     #######  ##  ##";
	@echo "$(RESET)";

$(BONUS): $(OBJ_BONUS) $(OBJ_LIB) $(OBJ)
	@$(CC) $(OBJ_LIB) $(OBJ) $(OBJ_BONUS) -o $(BONUS)
	@echo "$(YELLOW)"
	@echo " ######    #####   ##   ##  ##   ##   #####"
	@echo "  ##  ##  ##   ##  ###  ##  ##   ##  ##   ##"
	@echo "  ##  ##  ##   ##  #### ##  ##   ##  #"
	@echo "  #####   ##   ##  ## ####  ##   ##   #####"
	@echo "  ##  ##  ##   ##  ##  ###  ##   ##       ##"
	@echo "  ##  ##  ##   ##  ##   ##  ##   ##  ##   ##"
	@echo " ######    #####   ##   ##   #####    #####"
	@echo "$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(OBJ_LIB) $(OBJ_BONUS) $(OBJ_MAIN)
	@echo "$(RED)clean$(RESET)";

fclean: clean
	@echo "$(YELLOW)remove$(YELLOW) $(RED)$(NAME)$(RESET)";
	@rm -f $(NAME)
	@rm -f $(BONUS)

re: fclean all
	@echo "$(NAME) restart"

.PHONY: all clean fclean re
