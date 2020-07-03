#!/bin/bash
clang -g -o objtest -I includes -I libft/includes -Llibft -lft objtest.c src/obj_loader.c src/mesh.c
