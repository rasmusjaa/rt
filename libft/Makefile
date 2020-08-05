# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 15:22:37 by wkorande          #+#    #+#              #
#    Updated: 2020/08/03 14:01:06 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

BLACK=\033[30m
RED=\033[0;31m
BOLDRED=\033[1;31m
GREEN=\033[0;32m
BOLDGREEN=\033[1;32m
YELLOW=\033[0;33m
BOLDYELLOW=\033[1;33m
BLUE=\033[0;34m
BOLDBLUE=\033[1;34m
PINK=\033[0;35m
BOLDPINK=\033[1;35m
CYAN=\033[0;36m
BOLDCYAN=\033[1;36m
WHITE=\033[37m
NORMAL=\033[0m

SRC = ft_abs.c\
		ft_abs_d.c\
		ft_dtoa.c\
		ft_get_next_line.c\
		ft_inv_lerp_d.c\
		ft_inv_lerp_f.c\
		ft_itoa_base.c\
		ft_itoa_base_ull.c\
		ft_itoa_ll.c\
		ft_itoa_ull.c\
		ft_lerp_d.c\
		ft_lerp_f.c\
		ft_make_pair_d.c\
		ft_map_range.c\
		ft_max.c\
		ft_max_d.c\
		ft_min.c\
		ft_ndigits.c\
		ft_ndigits_base.c\
		ft_ndigits_base_ll.c\
		ft_ndigits_base_ull.c\
		ft_ndigits_d.c\
		ft_nwords.c\
		ft_pow.c\
		ft_strrev.c\
		ft_strtod.c\
		ft_strtok.c\
		ft_swap_d.c\
		ft_swap_f.c\
		ft_clamp_d.c\
		ft_clamp_d0.c\
		ft_deg_to_rad.c\
		ft_rad_to_deg.c\
		ft_rand_d.c\
		ft_free_array.c\
		ft_clamp_range.c\
		ft_pow_d.c

LIBC_SRC = ft_atoi.c\
		ft_bzero.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_memalloc.c\
		ft_memccpy.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memdel.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar.c\
		ft_putchar_fd.c\
		ft_putendl.c\
		ft_putendl_fd.c\
		ft_putnbr.c\
		ft_putnbr_fd.c\
		ft_putstr.c\
		ft_putstr_fd.c\
		ft_strcat.c\
		ft_strchr.c\
		ft_strclr.c\
		ft_strcmp.c\
		ft_strcpy.c\
		ft_strdel.c\
		ft_strdup.c\
		ft_strequ.c\
		ft_striter.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlen.c\
		ft_strmap.c\
		ft_strmapi.c\
		ft_strncat.c\
		ft_strncmp.c\
		ft_strncpy.c\
		ft_strnequ.c\
		ft_strnew.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strsplit.c\
		ft_strstr.c\
		ft_strsub.c\
		ft_strtrim.c\
		ft_tolower.c\
		ft_toupper.c

LIST_SRC = ft_lstadd.c\
		ft_lstappend.c\
		ft_lstdel.c\
		ft_lstdelone.c\
		ft_lstiter.c\
		ft_lstmap.c\
		ft_lstnew.c\
		ft_lstat.c\
		ft_lstsize.c\
		ft_lstnewptr.c

HT_SRC = ft_ht_create.c\
		ft_ht_destroy.c\
		ft_ht_del.c\
		ft_ht_get.c\
		ft_ht_set.c\
		ft_ht_hash_str.c\
		ft_ht_hash_int.c\
		ft_ht_print.c

Q_SRC = ft_queue_dequeue.c\
		ft_queue_print.c\
		ft_queue_enqueue.c\
		ft_queue_isempty.c\
		ft_queue_destroy.c\
		ft_queue_create.c

ST_SRC = ft_stack_create.c\
		ft_stack_push.c\
		ft_stack_pop.c\
		ft_stack_isempty.c\
		ft_stack_destroy.c

PF_SRC = ft_printf.c\
		ft_sprintf.c\
		ft_pbuf.c\
		ft_handle_str.c\
		ft_handle_nbr.c\
		ft_handle_other.c\
		ft_output.c\
		ft_parse.c\
		ft_cast_helper.c\
		ft_flags.c

VEC3_SRC = ft_add_vec3.c\
		ft_div_vec3.c\
		ft_dot_vec3.c\
		ft_invert_vec3.c\
		ft_len_vec3.c\
		ft_make_vec3.c\
		ft_mul_vec3.c\
		ft_mul_vec3_vec3.c\
		ft_normalize_vec3.c\
		ft_reflect_vec3.c\
		ft_set_vec3.c\
		ft_sub_vec3.c\
		ft_cross_vec3.c\
		ft_rotate_vec3.c\
		ft_parse_vec3.c\
		ft_clamp_vec3.c\
		ft_make_vec2i.c\
		ft_set_vec2i.c\
		ft_get_vec2i.c\
		ft_make_vec2.c\
		ft_add_vec2.c\
		ft_div_vec2.c\
		ft_dot_vec2.c\
		ft_invert_vec2.c\
		ft_len_vec2.c\
		ft_normalize_vec2.c\
		ft_sub_vec2.c\
		ft_mul_vec2.c\
		ft_parse_vec2.c\
		ft_refract_vec3.c

MATRIX_SRC = ft_create_rot_mat4.c\
		ft_create_rotx_mat4.c\
		ft_create_roty_mat4.c\
		ft_create_rotz_mat4.c\
		ft_create_scale_mat4.c\
		ft_create_trans_mat4.c\
		ft_ident_mat4.c\
		ft_lookat_mat4.c\
		ft_mul_dir_vec3_mat4.c\
		ft_mul_mat4_mat4.c\
		ft_mul_vec3_mat4.c\
		ft_trs_mat4.c\
		ft_print_mat4.c\
		ft_transpose_mat4.c

COLOR_SRC = ft_add_rgba.c\
		ft_add_rgba_uc.c\
		ft_clamp_rgba.c\
		ft_get_color.c\
		ft_lerp_rgba.c\
		ft_make_rgba.c\
		ft_mul_rgba.c\
		ft_mul_rgba_rgba.c\
		ft_sub_rgba.c\
		ft_parse_rgba.c\
		ft_blend_rgba.c\
		ft_intensity_rgba.c\
		ft_div_rgba.c

SRCDIR = srcs

LIBC_SRCDIR = $(SRCDIR)/libc
LIST_SRCDIR = $(SRCDIR)/list
HT_SRCDIR = $(SRCDIR)/hashtable
Q_SRCDIR = $(SRCDIR)/queue
ST_SRCDIR = $(SRCDIR)/stack
PF_SRCDIR = $(SRCDIR)/ft_printf
VEC3_SRCDIR = $(SRCDIR)/vector
MATRIX_SRCDIR = $(SRCDIR)/matrix
COLOR_SRCDIR = $(SRCDIR)/color

SRCS =	$(addprefix $(SRCDIR)/, $(SRC))\
		$(addprefix $(LIBC_SRCDIR)/, $(LIBC_SRC))\
		$(addprefix $(LIST_SRCDIR)/, $(LIST_SRC))\
		$(addprefix $(HT_SRCDIR)/, $(HT_SRC))\
		$(addprefix $(Q_SRCDIR)/, $(Q_SRC))\
		$(addprefix $(ST_SRCDIR)/, $(ST_SRC))\
		$(addprefix $(PF_SRCDIR)/, $(PF_SRC))\
		$(addprefix $(VEC3_SRCDIR)/, $(VEC3_SRC))\
		$(addprefix $(MATRIX_SRCDIR)/, $(MATRIX_SRC))\
		$(addprefix $(COLOR_SRCDIR)/, $(COLOR_SRC))



OUT =  $(notdir $(SRCS:.c=.o)) #$(SRC:.c=.o) $(PF_SRC:.c=.o) $(VEC3_SRC:.c=.o)

INCL = includes

CC = clang

all: $(NAME)

$(NAME):
	@printf "$(BOLDYELLOW)%s$(NORMAL)\n" "Making $(NAME)"
	@$(CC) -Wall -Wextra -Werror -I $(INCL) -c $(SRCS)
	@ar rc $(NAME) $(OUT)
	@ranlib $(NAME)
	@printf "$(YELLOW)%s$(NORMAL)\n" "done"

debug:
	@printf "$(BOLDYELLOW)%s$(NORMAL)\n" "Making debug $(NAME)"
	@$(CC) -g -Wall -Wextra -Werror -I $(INCL) -c $(SRCS)
	@ar rc $(NAME) $(OUT)
	@ranlib $(NAME)
	@printf "$(YELLOW)%s$(NORMAL)\n" "done"

gnlbuff1:
	@printf "$(BOLDYELLOW)%s$(NORMAL)\n" "Making $(NAME)"
	@$(CC) -Wall -Wextra -Werror -DBUFF_SIZE1 -I $(INCL) -c $(SRCS)
	@ar rc $(NAME) $(OUT)
	@ranlib $(NAME)
	@printf "$(YELLOW)%s$(NORMAL)\n" "done"

clean:
	@printf "$(BOLDBLUE)%s$(NORMAL)\n" "Removing $(OUT)"
	@rm -f $(OUT)
	@printf "$(BLUE)%s$(NORMAL)\n" "done"

fclean: clean
	@printf "$(BOLDBLUE)%s$(NORMAL)\n" "Removing $(NAME)"
	@rm -f $(NAME)
	@printf "$(BLUE)%s$(NORMAL)\n" "done"

re: fclean all

.PHONY: all clean fclean re
