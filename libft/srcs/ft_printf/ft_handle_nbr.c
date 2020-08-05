/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:41:22 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/31 11:51:53 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_handle_di(t_pf_env *env, va_list valist)
{
	char		*str;
	long long	n;
	int			bytes;

	n = ft_cast_signed(env->length, valist);
	if (n < 0)
		ft_set_prefix(env, "-", 1);
	else
	{
		if (env->plus)
			ft_set_prefix(env, "+", 1);
		if (!env->plus && env->space)
			ft_set_prefix(env, " ", 1);
	}
	if (env->precision_specified)
		env->zero_specified = 0;
	if (env->precision_specified && env->precision == 0)
		str = ft_strdup("");
	else
		str = ft_itoa_ull(n < 0 ? (long long)(n * -1) : (long long)n);
	bytes = ft_format_zp(env, str, ft_strlen(str));
	free(str);
	return (bytes);
}

int	ft_handle_o(t_pf_env *env, va_list valist)
{
	char				*str;
	unsigned long long	n;
	int					bytes;

	n = ft_cast_unsigned(env->length, valist);
	if (env->precision_specified)
	{
		env->zero_specified = 0;
		env->precision -= (n != 0) ? env->hash : 0;
	}
	if (env->hash && n != 0)
		ft_set_prefix(env, ZERO, 1);
	if (env->precision_specified && env->precision == 0 && !env->hash)
		str = ft_strdup("");
	else
		str = ft_itoa_base_ull(n, BASE8);
	bytes = ft_format_zp(env, str, ft_strlen(str));
	free(str);
	return (bytes);
}

int	ft_handle_u(t_pf_env *env, va_list valist)
{
	char				*str;
	unsigned long long	n;
	int					bytes;

	n = ft_cast_unsigned(env->length, valist);
	if (env->precision_specified)
		env->zero_specified = 0;
	if (env->precision_specified && env->precision == 0)
		str = ft_strdup("");
	else
		str = ft_itoa_ull(n);
	bytes = ft_format_zp(env, str, ft_strlen(str));
	free(str);
	return (bytes);
}

int	ft_handle_f(t_pf_env *env, va_list valist)
{
	char		*str;
	long double	d;
	int			bytes;

	if (!env->precision_specified)
		env->precision = 6;
	d = ft_cast_double(env->length, valist);
	if (d < 0)
		ft_set_prefix(env, "-", 1);
	else
	{
		if (env->plus)
			ft_set_prefix(env, "+", 1);
		if (!env->plus && env->space)
			ft_set_prefix(env, " ", 1);
	}
	if (env->minus)
		env->zero_specified = 0;
	if (env->hash && env->precision_specified && env->precision == 0)
		str = ft_strjoin(ft_dtoa((d < 0 ? -d : d), env->precision), ".");
	else
		str = ft_dtoa((d < 0 ? -d : d), env->precision);
	bytes = ft_format_zp(env, str, ft_strlen(str));
	free(str);
	return (bytes);
}
