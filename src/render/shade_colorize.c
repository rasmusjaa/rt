/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_colorize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 14:07:11 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 14:07:35 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <stdlib.h>

t_rgba	colorize(size_t colorize, t_rgba color)
{
	double	c;
	t_rgba	copy;

	copy.r = color.r;
	copy.g = color.g;
	copy.b = color.b;
	copy.a = color.a;

	if (colorize)
	{
		c = ft_intensity_rgba(color);
		if (colorize == 1)
			color = ft_make_rgba(c, c, c, color.a);
		else if (colorize == 2)
			color = ft_sub_rgba(ft_make_rgba(1, 1, 1, 1), color);
		else if (colorize == 3)
		{
			color.r = (copy.r * .393) + (copy.g *.769) + (copy.b * .189);
			color.g = (copy.r * .349) + (copy.g *.686) + (copy.b * .168);
			color.b = (copy.r * .272) + (copy.g *.534) + (copy.b * .131);
		}
		else if (colorize == 4)
			color = ft_make_rgba(c, 0, 0, color.a);
		else if (colorize == 5)
			color = ft_make_rgba(0, c, 0, color.a);
		else if (colorize == 6)
			color = ft_make_rgba(0, 0, c, color.a);

	}
	return (ft_clamp_rgba(color));
}
