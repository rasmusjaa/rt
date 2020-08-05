/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_vec2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:23:55 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/07 15:42:09 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec2	ft_normalize_vec2(t_vec2 v)
{
	t_vec2 new;
	double l;

	l = ft_len_vec2(v);
	new = ft_div_vec2(v, l);
	return (new);
}
