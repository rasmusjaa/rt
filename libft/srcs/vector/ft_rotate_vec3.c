/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_vec3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 20:56:32 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/01 18:19:15 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"
#include <math.h>

t_vec3	ft_rotate_vec3_x(t_vec3 v, double a)
{
	t_vec3 res;

	res.x = v.x;
	res.y = v.y * cos(a) + v.z * sin(a);
	res.z = -v.y * sin(a) + v.z * cos(a);
	return (res);
}

t_vec3	ft_rotate_vec3_y(t_vec3 v, double a)
{
	t_vec3 res;

	res.x = v.x * cos(a) + v.z * sin(a);
	res.y = v.y;
	res.z = -v.x * sin(a) + v.z * cos(a);
	return (res);
}

t_vec3	ft_rotate_vec3_z(t_vec3 v, double a)
{
	t_vec3 res;

	res.x = v.x * cos(a) - v.y * sin(a);
	res.y = v.x * sin(a) + v.y * cos(a);
	res.z = v.z;
	return (res);
}

/*
** rotates vec3 by rot (degrees) in XYZ order
*/

t_vec3	ft_rotate_vec3(t_vec3 v, t_vec3 rot)
{
	v = ft_rotate_vec3_x(v, ft_deg_to_rad(rot.x));
	v = ft_rotate_vec3_y(v, ft_deg_to_rad(rot.y));
	v = ft_rotate_vec3_z(v, ft_deg_to_rad(rot.z));
	return (v);
}
