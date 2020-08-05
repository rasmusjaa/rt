/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:11:35 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 12:48:06 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_rgba	ft_get_rgba(int color)
{
	return (ft_make_rgba(
		(double)((color >> (16)) & 0xff) / 255.0,
		(double)((color >> (8)) & 0xff) / 255.0,
		(double)((color >> (0)) & 0xff) / 255.0,
		1.0));
}

int		ft_get_color(t_rgba c)
{
	int r;
	int g;
	int b;

	r = 0;
	g = 0;
	b = 0;
	r = (int)(c.r * 255.0f) << 16;
	g = (int)(c.g * 255.0f) << 8;
	b = (int)(c.b * 255.0f);
	return (r | g | b);
}
