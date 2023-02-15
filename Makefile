# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 23:40:00 by mmariani          #+#    #+#              #
#    Updated: 2023/02/15 04:28:43 by mmariani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosopher

SRCS = philosopher.c mutex.c action.c routine.c utils.c monitor.c check.c

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRCS) -pthread -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re