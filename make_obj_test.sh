#!/bin/bash
clang -g -I./includes -I./libft/includes objtest.c src/obj_loader.c src/mesh.c -Llibft -lft -o obj_test
