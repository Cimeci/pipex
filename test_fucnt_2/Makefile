# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 09:23:44 by inowak--          #+#    #+#              #
#    Updated: 2024/12/17 09:27:02 by inowak--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 
NAME = pipex

SRCS = gnl/get_next_line.c gnl/get_next_line_utils.c main.c

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

OBJS = $(SRCS:.c=.o)

all: $(NAME)
	@echo "compiled";

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re
