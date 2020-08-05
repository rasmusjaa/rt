/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_colorize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 14:07:11 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 15:29:57 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "color.h"
#include <stdlib.h>

t_rgba	colorize(size_t colorize, t_rgba color)
{
	double	c;
	t_rgba	copy;

	copy = color;
	if (colorize)
	{
		c = ft_intensity_rgba(color);
		if (colorize == COLORIZE_GRAY)
			color = ft_make_rgba(c, c, c, color.a);
		else if (colorize == COLORIZE_INVERT)
			color = ft_sub_rgba(ft_make_rgba(1, 1, 1, 1), color);
		else if (colorize == COLORIZE_SEPIA)
		{
			color.r = (copy.r * 0.393) + (copy.g * 0.769) + (copy.b * 0.189);
			color.g = (copy.r * 0.349) + (copy.g * 0.686) + (copy.b * 0.168);
			color.b = (copy.r * 0.272) + (copy.g * 0.534) + (copy.b * 0.131);
		}
		else if (colorize == COLORIZE_RED)
			color = ft_make_rgba(c, 0, 0, color.a);
		else if (colorize == COLORIZE_GREEN)
			color = ft_make_rgba(0, c, 0, color.a);
		else if (colorize == COLORIZE_BLUE)
			color = ft_make_rgba(0, 0, c, color.a);
	}
	return (ft_clamp_rgba(color));
}
