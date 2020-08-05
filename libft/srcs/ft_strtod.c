/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:28:06 by wkorande          #+#    #+#             */
/*   Updated: 2020/02/06 14:01:45 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_vars(double *d, int *n, int *dig, int *dec)
{
	*d = 0.0;
	*n = 0;
	*dig = 0;
	*dec = 0;
}

static void	check_sign(char **s, int *negptr)
{
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			*negptr = 1;
		(*s)++;
	}
}

double		ft_strtod(char *s)
{
	double	nbr;
	int		negative;
	int		digits;
	int		decimals;

	while (*s == ' ')
		s++;
	init_vars(&nbr, &negative, &digits, &decimals);
	check_sign(&s, &negative);
	while (ft_isdigit(*s) || (digits++))
	{
		nbr = nbr * 10.0 + (*(s++) - '0');
	}
	if (*s == '.')
	{
		s++;
		while (ft_isdigit(*s) && (digits += 1) && (decimals += 1))
		{
			nbr = nbr * 10.0 + (*s - '0');
			s++;
		}
	}
	while (decimals--)
		nbr /= 10.0;
	return (negative ? -nbr : nbr);
}
