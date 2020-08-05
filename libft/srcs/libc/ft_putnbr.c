/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:34:31 by wkorande          #+#    #+#             */
/*   Updated: 2019/10/16 17:36:01 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long long_nb;

	long_nb = n;
	if (long_nb < 0)
	{
		ft_putchar('-');
		long_nb = long_nb * -1;
	}
	if (long_nb < 10)
	{
		ft_putchar('0' + long_nb);
	}
	else
	{
		ft_putnbr(long_nb / 10);
		ft_putnbr(long_nb % 10);
	}
}
