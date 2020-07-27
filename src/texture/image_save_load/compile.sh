#!/bin/bash

gcc ../../../libft/srcs/ft_get_next_line.c test.c image_data.c load_ppm.c ../../../libft/libft.a -I ../../../libft/includes -L ../../../libft -lmlx -lm -framework OpenGL -framework AppKit 
