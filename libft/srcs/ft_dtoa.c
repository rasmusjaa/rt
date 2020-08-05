/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 10:36:01 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/15 11:34:30 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char			*ft_fractoa(long double d, int precision, int *pass)
{
	char	*str;
	int		i;

	i = 0;
	d = d < 0 ? -d : d;
	d -= (long double)(unsigned long long)d;
	d = d + (0.5 / ft_pow(10, precision));
	if (!(str = (char*)ft_memalloc(precision + 1)))
		return (NULL);
	if (d >= 1.0)
	{
		*pass = 1;
		d -= (long double)(unsigned long long)d;
	}
	while (i < precision)
	{
		d *= 10;
		if ((int)d > 10)
			return (NULL);
		str[i++] = (int)d + '0';
		d -= (long double)(unsigned long long)d;
	}
	return (str);
}

static char			*ft_dectoa(long double d)
{
	char		*str;
	char		*ptr;
	int			count;
	int			i;
	long double	d_tmp;

	count = ft_ndigits_base_ll(d, 10);
	if (!(str = (char*)ft_memalloc(count + 1)))
		return (NULL);
	ptr = str;
	while (count)
	{
		i = count - 1;
		d_tmp = d;
		while (i--)
			d_tmp /= 10;
		*ptr++ = (int)d_tmp + '0';
		d_tmp = (int)d_tmp;
		while (++i < count - 1)
			d_tmp *= 10;
		d -= d_tmp;
		count--;
	}
	return (str);
}

char				*ft_dtoa(long double d, int precision)
{
	char	*str;
	char	*dec;
	char	*frac;
	char	*dot;
	int		pass;

	pass = 0;
	if (!precision)
	{
		frac = ft_fractoa(d, precision, &pass);
		return (pass ?
			ft_itoa_ll((long long)d + 1) : ft_itoa_ll((long long)d));
	}
	frac = ft_fractoa(d, precision, &pass);
	if (pass)
		dec = ft_dectoa(d + 1);
	else
		dec = ft_dectoa(d);
	dot = ft_strjoin(dec, ".");
	str = ft_strjoin(dot, frac);
	free(dot);
	free(dec);
	free(frac);
	return (str);
}
