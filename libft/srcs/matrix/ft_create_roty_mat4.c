/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_roty_mat4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:58:50 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/21 12:00:29 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>

t_mat4x4	ft_create_roty_mat4(float angle)
{
	t_mat4x4 mat;

	mat = ft_ident_mat4();
	mat.m[0][0] = cos(angle);
	mat.m[0][2] = -sin(angle);
	mat.m[1][1] = 1.0f;
	mat.m[2][0] = sin(angle);
	mat.m[2][2] = cos(angle);
	return (mat);
}
