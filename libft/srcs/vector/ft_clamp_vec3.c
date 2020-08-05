/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp_vec3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:55:38 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/08 10:56:53 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

t_vec3	ft_clamp_vec3(t_vec3 v, double min, double max)
{
	ft_clamp_d(v.x, min, max);
	ft_clamp_d(v.y, min, max);
	ft_clamp_d(v.z, min, max);
	return (v);
}
