/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_vec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:04:20 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/16 14:14:07 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	ft_div_vec3(t_vec3 v, double t)
{
	t_vec3 new;

	if (t == 0.0)
		return (v);
	new.x = v.x / t;
	new.y = v.y / t;
	new.z = v.z / t;
	return (new);
}
