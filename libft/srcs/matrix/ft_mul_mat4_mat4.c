/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mul_mat4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:50:27 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/21 10:51:18 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat4x4	ft_mul_mat4_mat4(t_mat4x4 a, t_mat4x4 b)
{
	t_mat4x4	c;
	int			x;
	int			y;
	int			i;

	c = ft_ident_mat4();
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			i = 0;
			while (i < 4)
			{
				c.m[y][x] += a.m[y][i] * b.m[i][x];
				i++;
			}
			x++;
		}
		y++;
	}
	return (c);
}
