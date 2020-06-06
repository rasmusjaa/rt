# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2020/06/06 09:45:42 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = readtest

SRCS =	src/read_csv.c \
		src/main.c

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

INCL = -I libft/includes/ -I includes

LIB = -L libft -lft -lm

CC = clang

all: $(NAME)

$(NAME): libftmake
	$(CC) $(FLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME) -O2

libftmake:
	@make -C libft

clean:
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

run:
	$(CC) $(FLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME) -O2
	./readtest scene1.csv

.PHONY: all libftmake clean fclean re run