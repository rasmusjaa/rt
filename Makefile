# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2020/06/04 15:11:28 by rjaakonm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = readtest

SRCS =	read_csv.c \
		main.c

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

INCL = -I libft/includes/ -I includes

LIB = -L libft -lft

.PHONY: all clean fclean re run

all: $(NAME)

$(NAME): libftmake
	gcc $(FLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME) -O2

libftmake:
	@make -C libft

clean:
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

run:
	gcc $(FLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME) -O2
	./readtest scene1.csv
