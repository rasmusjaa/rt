/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 18:54:11 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/01 17:23:54 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long			ft_cast_signed(int length, va_list valist)
{
	long long n;

	if (length == LEN_HH)
		n = (char)va_arg(valist, int);
	else if (length == LEN_H)
		n = (short)va_arg(valist, int);
	else if (length == LEN_L)
		n = (long)va_arg(valist, long);
	else if (length == LEN_LL)
		n = (long long)va_arg(valist, long long);
	else
		n = va_arg(valist, int);
	return (n);
}

unsigned long long	ft_cast_unsigned(int length, va_list valist)
{
	unsigned long long n;

	if (length == LEN_HH)
		n = (unsigned char)va_arg(valist, unsigned int);
	else if (length == LEN_H)
		n = (unsigned short)va_arg(valist, unsigned int);
	else if (length == LEN_L)
		n = (unsigned long)va_arg(valist, unsigned long);
	else if (length == LEN_LL)
		n = (unsigned long long)va_arg(valist, unsigned long long);
	else
		n = va_arg(valist, unsigned int);
	return (n);
}

long double			ft_cast_double(int length, va_list valist)
{
	long double d;

	if (length == LEN_LD)
		d = va_arg(valist, long double);
	else
		d = va_arg(valist, double);
	return (d);
}
