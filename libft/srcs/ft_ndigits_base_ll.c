/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ndigits_base_ll.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:22:51 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/15 11:37:20 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ndigits_base_ll(long long n, int base)
{
	int i;

	i = 0;
	while (n != 0)
	{
		n /= base;
		i++;
	}
	return (ft_max(1, i));
}
