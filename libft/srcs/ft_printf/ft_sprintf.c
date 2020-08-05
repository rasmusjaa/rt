/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 11:36:54 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/31 11:39:38 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

int	ft_sprintf(char *str, const char *format, ...)
{
	va_list	valist;
	int		bytes;

	va_start(valist, format);
	bytes = ft_vsprintf(str, format, valist);
	va_end(valist);
	return (bytes);
}
