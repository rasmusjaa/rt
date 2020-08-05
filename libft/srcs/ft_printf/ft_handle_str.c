/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:25:24 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/31 11:51:26 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_handle_c(t_pf_env *env, va_list valist)
{
	char c;

	c = va_arg(valist, int);
	return (ft_format(env, &c, 1));
}

int	ft_handle_s(t_pf_env *env, va_list valist)
{
	char	*s;
	int		len;

	s = va_arg(valist, char *);
	if (!s)
		s = NULL_STRING;
	if (env->precision_specified)
		len = ft_min(ft_strlen(s), env->precision);
	else
		len = ft_strlen(s);
	return (ft_format(env, s, len));
}
