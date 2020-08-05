/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_rgba.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 22:06:21 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/29 22:12:55 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_rgba	ft_div_rgba(t_rgba c, double t)
{
	if (t == 0.0)
		return (c);
	c.r /= t;
	c.g /= t;
	c.b /= t;
	c = ft_clamp_rgba(c);
	return (c);
}
