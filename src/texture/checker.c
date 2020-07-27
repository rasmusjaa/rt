/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:01:24 by sluhtala          #+#    #+#             */
/*   Updated: 2020/07/27 16:19:00 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double dmodulo(double d, double m)
{
	double mod;

	mod = (d) - (floor((d) / (double)m) * m);
	return (mod);
}

t_rgba checker_texture(t_texture *texture, double v, double u)
{
	float size = 0.1;
	t_rgba col1 = texture->color1;
	t_rgba col2 = texture->color2;

	if (dmodulo(u, size * 2) < size)
	{
		if (dmodulo(v, size * 2) < size)
		{
			return col1;
		}
		else 
		{
			return col2;
		}
	}	
	else 
	{
		if (dmodulo(v, size * 2) < size)
		{
			return col2;
		}
		else 
		{
			return col1;
		}

	}
	return (ft_make_rgba(0, 0, 0, 1));
}
