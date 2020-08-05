/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transpose_mat4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:08:56 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/22 18:22:00 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "libft.h"

t_mat4x4	ft_transpose_mat4(t_mat4x4 m)
{
	t_mat4x4	t;
	int			i;

	i = 0;
	while (i < 4)
	{
		t.m[i][0] = m.m[0][i];
		t.m[i][1] = m.m[1][i];
		t.m[i][2] = m.m[2][i];
		t.m[i][3] = m.m[3][i];
		i++;
	}
	return (t);
}
