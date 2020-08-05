/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:48:42 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/09 18:23:39 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

t_sp_type	g_output_types[N_HANDLERS] =
{
	{'c', ft_handle_c},
	{'s', ft_handle_s},
	{'p', ft_handle_p},
	{'d', ft_handle_di},
	{'i', ft_handle_di},
	{'o', ft_handle_o},
	{'u', ft_handle_u},
	{'x', ft_handle_x_low},
	{'X', ft_handle_x_up},
	{'f', ft_handle_f}
};

int			ft_output_type(va_list valist, char c, t_pf_env *env)
{
	int i;
	int bytes;

	bytes = 0;
	i = 0;
	while (i < N_HANDLERS)
	{
		if (g_output_types[i].c == c)
			bytes = g_output_types[i].output_func(env, valist);
		i++;
	}
	return (bytes);
}

static int	ft_output_format(char **fstr, t_pf_env *env, va_list valist)
{
	int bytes;

	if (*(*fstr) == '\0')
		return (-1);
	bytes = 0;
	ft_init_env(env);
	while (ft_parse_flags(fstr, env) || ft_parse_width(fstr, env, valist) ||
		ft_parse_precision(fstr, env, valist) || ft_parse_length(fstr, env))
		bytes = 0;
	if (*(*fstr) == '\0')
		return (-1);
	bytes += ft_output_type(valist, *(*fstr), env);
	if (*(*fstr) == '%')
		bytes += ft_handle_percent(env);
	(*fstr)++;
	return (bytes);
}

static int	ft_output_nonformat(t_pf_env *env, char **fstr)
{
	int bytes;

	bytes = 0;
	while (*(*fstr) && *(*fstr) != '%')
	{
		bytes += ft_outchar(env, *fstr, 1);
		(*fstr)++;
	}
	return (bytes);
}

int			ft_vsprintf(char *str, const char *format, va_list valist)
{
	t_pf_env	*env;
	char		*fstr;
	size_t		bytes;

	if (!(env = ft_create_env()))
		return (-1);
	if (!(env->p_buf = ft_create_p_buf(str)))
		return (-1);
	fstr = (char*)format;
	while (*fstr)
	{
		if (*fstr == '%')
		{
			fstr++;
			ft_output_format(&fstr, env, valist);
		}
		else
			ft_output_nonformat(env, &fstr);
	}
	bytes = env->p_buf->at - env->p_buf->start;
	free(env->p_buf);
	free(env);
	return (bytes);
}

int			ft_printf(const char *format, ...)
{
	t_pf_env	*env;
	char		*fstr;
	size_t		bytes;
	va_list		valist;

	if (!format)
		return (-1);
	if (*format == '\0')
		return (0);
	if (!(env = ft_create_env()))
		return (-1);
	env->p_buf = NULL;
	bytes = 0;
	fstr = (char*)format;
	va_start(valist, format);
	while (*fstr)
	{
		if (*fstr == '%' && (fstr++))
			bytes += ft_output_format(&fstr, env, valist);
		else
			bytes += ft_output_nonformat(env, &fstr);
	}
	va_end(valist);
	free(env);
	return (bytes);
}
