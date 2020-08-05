/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_vec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:24:56 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/07 15:31:25 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

double	ft_len_vec2(t_vec2 v)
{
	double l;

	if (v.x == 0.0 && v.y == 0.0)
		return (0.0);
	l = sqrt((v.x * v.x) + (v.y * v.y));
	return (l);
}
