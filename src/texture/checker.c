/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:01:24 by sluhtala          #+#    #+#             */
/*   Updated: 2020/07/15 17:58:30 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rgba checker_texture(double v, double u)
{
	float size = 0.03;
	t_rgba col1 = ft_make_rgba(1, 1, 1, 1);
	t_rgba col2 = ft_make_rgba(0, 0, 0, 1);

	if ((int)(u*1000) % (int)((size * 2)*1000) < (int)(size*1000))
	{
		if ((int)(v * 1000) % (int)((size * 2) * 1000) < (int)(size*1000))
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
		if ((int)(v*1000) % (int)((size * 2) * 1000) < (int)(size*1000))
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
