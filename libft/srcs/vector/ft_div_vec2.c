/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_vec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:28:15 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/07 15:40:15 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec2	ft_div_vec2(t_vec2 v, double t)
{
	t_vec2 new;

	if (t == 0)
		return (v);
	new.x = v.x / t;
	new.y = v.y / t;
	return (new);
}
