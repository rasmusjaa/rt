# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2020/08/03 17:09:31 by sluhtala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

SRCDIR = src

SRC = 	core/cube_map.c\
		core/event_hooks/events.c\
		core/event_hooks/keyboard.c\
		core/event_hooks/keyboard2.c\
		core/event_hooks/mouse.c\
		core/event_hooks/window.c\
		core/mlx.c\
		core/mlx_image.c\
		core/mlx_image2.c\
		core/load_ppm.c\
		core/load_ppm2.c\
		core/obj_loader.c\
		core/perlin_init.c\
		core/rt.c\
		core/thread_pool/ft_get_num_procs.c\
		core/thread_pool/tp.c\
		core/thread_pool/tp_job.c\
		core/thread_pool/tp_queue.c\
		debug/debug.c\
		debug/draw_line.c\
		main.c\
		mesh/mesh_calc_bounds.c\
		mesh/mesh_create.c\
		mesh/mesh_destroy.c\
		mesh/mesh_set_vert.c\
		octree/octree.c\
		render/shadow.c\
		render/raycast.c\
		render/render_scene.c\
		render/render_task.c\
		render/render_tile.c\
		scene/camera.c\
		scene/read_csv.c\
		scene/scene.c\
		scene/shape/bounds.c\
		scene/shape/cone.c\
		scene/shape/cylinder.c\
		scene/shape/model.c\
		scene/shape/plane.c\
		scene/shape/shape.c\
		scene/shape/sphere.c\
		scene/shape/triangle.c\
		texture/bricks.c\
		texture/checker.c\
		texture/material.c\
		texture/perlin.c\
		texture/texture.c

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
	./RT resources/scenes/simple.csv

.PHONY: all libftmake clean fclean re run debug
