/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_trans_mat4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:53:48 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/21 10:54:12 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "vector.h"

t_mat4x4	ft_create_trans_mat4(t_vec3 translation)
{
	t_mat4x4 mat;

	mat = ft_ident_mat4();
	mat.m[3][0] = translation.x;
	mat.m[3][1] = translation.y;
	mat.m[3][2] = translation.z;
	return (mat);
}
