# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2020/06/06 13:46:30 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt

SRCS =	src/read_csv.c \
		src/main.c

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

INCL = -I libft/includes/ -I includes

LIB = -L libft -lft -lm

CC = clang

all: $(NAME)

$(NAME): libftmake
	$(CC) $(FLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)

libftmake:
	@make -C libft

debug:
	$(CC) -g $(FLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)

clean:
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	#@make fclean -C libft

re: fclean all

run:
	$(CC) $(FLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME) -O2
	./readtest scene1.csv

.PHONY: all libftmake clean fclean re run