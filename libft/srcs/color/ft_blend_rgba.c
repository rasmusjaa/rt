/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blend_rgba.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:47:03 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/22 16:25:55 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_rgba	ft_blend_rgba(t_rgba c1, t_rgba c2)
{
	t_rgba c;

	c.r = (c1.r + c2.r) * 0.5;
	c.g = (c1.g + c2.g) * 0.5;
	c.b = (c1.b + c2.b) * 0.5;
	c.a = (c1.a + c2.a) * 0.5;
	c = ft_clamp_rgba(c);
	return (c);
}
