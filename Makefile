# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2020/07/28 14:58:08 by sluhtala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

SRCDIR = src

SRC = 	core/event_hooks/keyboard.c\
		core/event_hooks/mouse.c\
		core/event_hooks/window.c\
		core/mlx_image.c\
		core/obj_loader.c\
		core/rt.c\
		core/thread_pool/ft_get_num_procs.c\
		core/thread_pool/tp.c\
		core/thread_pool/tp_job.c\
		core/thread_pool/tp_queue.c\
		debug/debug.c\
		debug/draw_line.c\
		mesh/mesh_calc_bounds.c\
		mesh/mesh_create.c\
		mesh/mesh_destroy.c\
		mesh/mesh_set_vert.c\
		octree/octree.c\
		texture/material.c\
		texture/texture.c\
		texture/bricks.c\
		texture/checker.c\
		texture/texture_mapping.c\
		render/light.c\
		render/raycast.c\
		scene/camera.c\
		scene/read_csv.c\
		scene/shape/bounds.c\
		scene/shape/cone.c\
		scene/shape/cylinder.c\
		scene/shape/model.c\
		scene/shape/plane.c\
		scene/shape/shape.c\
		scene/shape/sphere.c\
		scene/shape/triangle.c\
		main.c\
		core/cube_map.c

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

libftdebug:
	@make debug -C libft

debug:
	$(CC) -g $(CFLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)

rebug: libftdebug
	$(CC) -g $(CFLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)

clean:
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

run:
	$(CC) $(CFLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)
	./RT resources/scenes/scene6.csv

.PHONY: all libftmake clean fclean re run debug
