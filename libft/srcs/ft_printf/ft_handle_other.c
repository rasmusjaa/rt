/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_other.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 11:42:28 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/31 11:51:44 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_handle_p(t_pf_env *env, va_list valist)
{
	char				*str;
	unsigned long long	p;
	int					bytes;

	env->hash = 1;
	ft_set_prefix(env, "0x", 2);
	p = va_arg(valist, unsigned long);
	if (!p)
		str = "0";
	else
		str = ft_itoa_base_ull(p, BASE16LOW);
	bytes = ft_format(env, str, ft_strlen(str));
	if (p)
		free(str);
	return (bytes);
}

int	ft_handle_x_low(t_pf_env *env, va_list valist)
{
	char				*str;
	unsigned long long	n;
	int					bytes;

	n = ft_cast_unsigned(env->length, valist);
	if (env->hash && n != 0)
		ft_set_prefix(env, "0x", 2);
	if (env->precision_specified)
		env->zero_specified = 0;
	if (env->precision_specified && env->precision == 0)
		str = ft_strdup("");
	else
		str = ft_itoa_base_ull(n, BASE16LOW);
	bytes = ft_format_zp(env, str, ft_strlen(str));
	free(str);
	return (bytes);
}

int	ft_handle_x_up(t_pf_env *env, va_list valist)
{
	char				*str;
	unsigned long long	n;
	int					bytes;

	n = ft_cast_unsigned(env->length, valist);
	if (env->hash && n != 0)
		ft_set_prefix(env, "0X", 2);
	if (env->precision_specified)
		env->zero_specified = 0;
	if (env->precision_specified && env->precision == 0)
		str = ft_strdup("");
	else
		str = ft_itoa_base_ull(n, BASE16UP);
	bytes = ft_format_zp(env, str, ft_strlen(str));
	free(str);
	return (bytes);
}

int	ft_handle_percent(t_pf_env *env)
{
	int bytes;

	if (env->minus && env->zero_specified)
		env->zero_specified = 0;
	bytes = ft_format_zp(env, PERCENT, 1);
	return (bytes);
}
