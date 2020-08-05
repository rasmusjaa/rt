/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_rotz_mat4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:59:25 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/21 12:00:16 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>

t_mat4x4	ft_create_rotz_mat4(float angle)
{
	t_mat4x4 mat;

	mat = ft_ident_mat4();
	mat.m[0][0] = cos(angle);
	mat.m[0][1] = -sin(angle);
	mat.m[1][0] = sin(angle);
	mat.m[1][1] = cos(angle);
	return (mat);
}
