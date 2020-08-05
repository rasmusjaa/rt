/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_vec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:04:52 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/16 14:14:19 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

double	ft_len_vec3(t_vec3 v)
{
	double l;

	if (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f)
		return (0.0f);
	l = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return (l);
}
