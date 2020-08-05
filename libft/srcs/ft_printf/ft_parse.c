/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 14:48:44 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/31 11:50:53 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		ft_parse_flags(char **fstr, t_pf_env *env)
{
	if (*(*fstr) == '#')
		env->hash = 1;
	else if (*(*fstr) == '0')
	{
		env->zero = 1;
		env->zero_specified = 1;
	}
	else if (*(*fstr) == '-')
		env->minus = 1;
	else if (*(*fstr) == '+')
		env->plus = 1;
	else if (*(*fstr) == ' ')
		env->space = 1;
	else
		return (0);
	(*fstr)++;
	return (1);
}

int		ft_parse_width(char **fstr, t_pf_env *env, va_list valist)
{
	int w;

	if ((w = ft_atoi(*fstr)) > 0 || *(*fstr) == '*')
	{
		if (*(*fstr) == '*')
		{
			w = va_arg(valist, int);
			if (w < 0)
				env->minus = 1;
			env->width = (w < 0 ? w * -1 : w);
			env->width_specified = 1;
			w = 1;
		}
		else
		{
			env->width = w;
			env->width_specified = 1;
		}
		(*fstr) += ft_ndigits(w);
		return (1);
	}
	return (0);
}

int		ft_parse_precision(char **fstr, t_pf_env *env, va_list valist)
{
	if (*(*fstr) == '.')
	{
		env->precision_specified = 1;
		env->precision = 0;
		(*fstr)++;
		if (ft_isdigit(*(*fstr)))
		{
			while (ft_isdigit(*(*fstr)))
			{
				env->precision = env->precision * 10 + (*(*fstr) - '0');
				(*fstr)++;
			}
		}
		else if (*(*fstr) == '*')
		{
			env->precision = va_arg(valist, int);
			(*fstr)++;
		}
		return (1);
	}
	return (0);
}

int		ft_parse_length(char **fstr, t_pf_env *env)
{
	if (*(*fstr) == 'h')
	{
		if (*(*fstr + 1) == 'h' && (*fstr)++)
			env->length = LEN_HH;
		else
			env->length = LEN_H;
		(*fstr)++;
		return (1);
	}
	else if (*(*fstr) == 'l')
	{
		if (*(*fstr + 1) == 'l' && (*fstr)++)
			env->length = LEN_LL;
		else
			env->length = LEN_L;
		(*fstr)++;
		return (1);
	}
	else if (*(*fstr) == 'L')
	{
		env->length = LEN_LD;
		(*fstr)++;
		return (1);
	}
	return (0);
}
