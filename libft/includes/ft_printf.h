/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:38:16 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/03 13:42:05 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>

# define N_HANDLERS 10
# define NULL_STRING "(null)"
# define BASE16LOW "0123456789abcdef"
# define BASE16UP "0123456789ABCDEF"
# define BASE10 "0123456789"
# define BASE8 "01234567"
# define PERCENT "%"
# define SPACE " "
# define ZERO "0"

# define LEN_NONE 0
# define LEN_HH 1
# define LEN_H 2
# define LEN_L 3
# define LEN_LL 4
# define LEN_LD 5

typedef struct		s_p_buf
{
	char			*start;
	char			*at;
	size_t			size;
}					t_p_buf;

typedef struct		s_pf_env
{
	t_p_buf			*p_buf;
	int				hash;
	int				zero_specified;
	int				zero;
	int				plus;
	int				minus;
	int				space;
	int				width_specified;
	int				width;
	int				width_left;
	int				precision_specified;
	int				precision;
	int				precision_left;
	int				length;
	int				prefix_specified;
	char			*prefix;
	int				prefixlen;
}					t_pf_env;

typedef int			(*t_s_func)(t_pf_env *, va_list);

typedef struct		s_sp_type
{
	char			c;
	t_s_func		output_func;
}					t_sp_type;

int					ft_printf(const char *format, ...);
int					ft_sprintf(char *str, const char *format, ...);
int					ft_vsprintf(char *str, const char *format, va_list valist);
t_pf_env			*ft_create_env(void);
void				ft_init_env(t_pf_env *env);
t_p_buf				*ft_create_p_buf(char *dest);
int					ft_resize_p_buf(t_p_buf *pbuf);
void				ft_set_prefix(t_pf_env *env, char *prefix, int len);
int					ft_parse_flags(char **fstr, t_pf_env *env);
int					ft_parse_width(char **fstr, t_pf_env *env, va_list valist);
int					ft_parse_precision(char **fstr, t_pf_env *env,
										va_list valist);
int					ft_parse_length(char **fstr, t_pf_env *env);
int					ft_format(t_pf_env *env, char *data, int len);
int					ft_format_zp(t_pf_env *env, char *data, int len);
int					ft_outchar(t_pf_env *env, const char *data,
										unsigned int len);
int					ft_handle_c(t_pf_env *env, va_list valist);
int					ft_handle_s(t_pf_env *env, va_list valist);
int					ft_handle_di(t_pf_env *env, va_list valist);
int					ft_handle_o(t_pf_env *env, va_list valist);
int					ft_handle_u(t_pf_env *env, va_list valist);
int					ft_handle_f(t_pf_env *env, va_list valist);
int					ft_handle_p(t_pf_env *env, va_list valist);
int					ft_handle_x_low(t_pf_env *env, va_list valist);
int					ft_handle_x_up(t_pf_env *env, va_list valist);
int					ft_handle_percent(t_pf_env *env);
long long			ft_cast_signed(int length, va_list valist);
unsigned long long	ft_cast_unsigned(int length, va_list valist);
long double			ft_cast_double(int length, va_list valist);

#endif
