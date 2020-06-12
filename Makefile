# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2020/06/12 17:16:32 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt

SRCDIR = src

SRC =	scene/read_csv.c\
		debug/debug.c\
		event_hooks/keyboard.c \
		event_hooks/mouse.c \
		event_hooks/window.c \
		camera.c\
		mlx_image.c\
		main.c\
		rt.c\
		thread_pool/tp.c\
		thread_pool/tp_job.c\
		thread_pool/tp_queue.c\
		thread_pool/ft_get_num_procs.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

INCL = -I libft/includes/ -I includes

UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux) # On Linux
        LIB = -L libft -lft -lmlx -lm -lXext -lX11 -pthread
    endif
    ifeq ($(UNAME_S),Darwin) # On MacOS
        LIB = -L libft -lft -lmlx -lm -framework OpenGL -framework AppKit
    endif

CC = clang

all: $(NAME)

$(NAME): libftmake
	$(CC) $(CFLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)

libftmake:
	@make -C libft

debug:
	$(CC) -g $(CFLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)

clean:
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

run:
	$(CC) $(CFLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)
	./rt resources/scene1.csv

.PHONY: all libftmake clean fclean re run debug
