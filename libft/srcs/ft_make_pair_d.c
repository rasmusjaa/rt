/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_pair_d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 00:03:47 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/20 15:10:04 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_pair_d	ft_make_pair_d(double a, double b)
{
	t_pair_d pair;

	pair.a = a;
	pair.b = b;
	return (pair);
}
