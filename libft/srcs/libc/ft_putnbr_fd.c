/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:34:31 by wkorande          #+#    #+#             */
/*   Updated: 2019/10/17 14:35:52 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long_nb;

	long_nb = n;
	if (long_nb < 0)
	{
		ft_putchar_fd('-', fd);
		long_nb = long_nb * -1;
	}
	if (long_nb < 10)
	{
		ft_putchar_fd('0' + long_nb, fd);
	}
	else
	{
		ft_putnbr_fd(long_nb / 10, fd);
		ft_putnbr_fd(long_nb % 10, fd);
	}
}
