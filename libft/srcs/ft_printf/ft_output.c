/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 14:17:39 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/31 11:51:06 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int			ft_format(t_pf_env *env, char *data, int len)
{
	int bytes;
	int padding;

	bytes = 0;
	padding = env->width - len - env->prefixlen;
	if (env->minus)
	{
		if (env->prefix_specified)
			bytes += ft_outchar(env, env->prefix, env->prefixlen);
		bytes += ft_outchar(env, data, len);
		while (padding-- > 0)
			bytes += ft_outchar(env, SPACE, 1);
	}
	else
	{
		while (padding-- > 0)
			bytes += ft_outchar(env, SPACE, 1);
		if (env->prefix_specified)
			bytes += ft_outchar(env, env->prefix, env->prefixlen);
		bytes += ft_outchar(env, data, len);
	}
	return (bytes);
}

static int	ft_format_zp_left(t_pf_env *env, char *data, int len)
{
	int bytes;

	bytes = 0;
	if (env->prefix_specified)
		bytes += ft_outchar(env, env->prefix, env->prefixlen);
	while (env->precision_left-- > 0)
		bytes += ft_outchar(env, ZERO, 1);
	bytes += ft_outchar(env, data, len);
	while (env->width_left-- > 0)
		bytes += ft_outchar(env, SPACE, 1);
	return (bytes);
}

static int	ft_format_zp_right(t_pf_env *env, char *data, int len)
{
	int bytes;

	bytes = 0;
	if (env->zero_specified && env->prefix_specified)
		bytes += ft_outchar(env, env->prefix, env->prefixlen);
	while (env->width_left-- > 0)
		bytes += ft_outchar(env, env->zero_specified ? ZERO : SPACE, 1);
	if (!env->zero_specified && env->prefix_specified)
		bytes += ft_outchar(env, env->prefix, env->prefixlen);
	while (env->precision_left-- > 0)
		bytes += ft_outchar(env, ZERO, 1);
	bytes += ft_outchar(env, data, len);
	return (bytes);
}

int			ft_format_zp(t_pf_env *env, char *data, int len)
{
	int bytes;

	bytes = 0;
	env->precision_left = 0;
	env->width_left = 0;
	if (env->precision_specified)
	{
		if (env->precision > len)
			env->precision_left = env->precision - len;
	}
	if (env->width_specified)
	{
		if (env->width > len + env->precision_left + env->prefixlen)
			env->width_left =
				env->width - len - env->prefixlen - env->precision_left;
	}
	if (env->minus)
		bytes += ft_format_zp_left(env, data, len);
	else
		bytes += ft_format_zp_right(env, data, len);
	return (bytes);
}

int			ft_outchar(t_pf_env *env, const char *data, unsigned int len)
{
	if (env && env->p_buf && env->p_buf->at)
	{
		while (len)
		{
			*(env->p_buf->at++) = *(data++);
			len--;
		}
		return (env->p_buf->at - env->p_buf->start);
	}
	write(1, data, len);
	return (len);
}
