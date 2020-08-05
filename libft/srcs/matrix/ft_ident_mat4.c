/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ident_mat4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:47:33 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/21 10:48:03 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat4x4	ft_ident_mat4(void)
{
	t_mat4x4	mat;
	int			y;
	int			x;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			mat.m[y][x] = x == y ? 1.0f : 0.0f;
			x++;
		}
		y++;
	}
	return (mat);
}
