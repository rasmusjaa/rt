/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_vec3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:05:37 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/16 15:11:02 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	ft_normalize_vec3(t_vec3 v)
{
	t_vec3 new;
	double l;

	l = ft_len_vec3(v);
	new = ft_div_vec3(v, l);
	return (new);
}
