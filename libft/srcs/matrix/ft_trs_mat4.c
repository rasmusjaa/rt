/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trs_mat4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:48:47 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/21 11:06:34 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "vector.h"

t_mat4x4	ft_trs_mat4(t_vec3 pos, t_vec3 rot, t_vec3 scale)
{
	t_mat4x4 trs;
	t_mat4x4 s;
	t_mat4x4 r;
	t_mat4x4 t;

	s = ft_create_scale_mat4(scale);
	r = ft_create_rot_mat4(rot);
	t = ft_create_trans_mat4(pos);
	trs = ft_mul_mat4_mat4(s, r);
	trs = ft_mul_mat4_mat4(trs, t);
	return (trs);
}
