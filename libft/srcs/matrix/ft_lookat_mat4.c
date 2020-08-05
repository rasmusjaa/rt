/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lookat_mat4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:37:38 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/21 16:15:47 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "vector.h"

t_mat4x4	ft_lookat_mat4(t_vec3 from, t_vec3 to, t_vec3 world_up)
{
	t_mat4x4	lookat;
	t_vec3		forward;
	t_vec3		right;
	t_vec3		up;

	lookat = ft_ident_mat4();
	forward = ft_normalize_vec3(ft_sub_vec3(from, to));
	right = ft_cross_vec3(ft_normalize_vec3(world_up), forward);
	up = ft_cross_vec3(forward, right);
	lookat.m[0][0] = right.x;
	lookat.m[0][1] = right.y;
	lookat.m[0][2] = right.z;
	lookat.m[1][0] = up.x;
	lookat.m[1][1] = up.y;
	lookat.m[1][2] = up.z;
	lookat.m[2][0] = forward.x;
	lookat.m[2][1] = forward.y;
	lookat.m[2][2] = forward.z;
	lookat.m[3][0] = from.x;
	lookat.m[3][1] = from.y;
	lookat.m[3][2] = from.z;
	return (lookat);
}
