/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bricks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:48:47 by sluhtala          #+#    #+#             */
/*   Updated: 2020/07/15 17:48:59 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"


t_rgba	brick_texture(t_texture *texture, double u, double v)
{
	int rows = (int)texture->settings.x;
	double mort_scale = texture->settings.y;
	double section_height = 1 / (double)rows;
	double brick_height = section_height / (1 + mort_scale);
	double mort_heigth = brick_height * mort_scale;

	u = 0;
	if (fmod(v, section_height) < mort_heigth)
		return (texture->color2);
	return (texture->color1);
	/*
	else
	{
		if (fmod(v, 2 * (rs + line_w)) < rs+line_w)
			u += line_w * 10;
		rs = ((1.0 - lines * 2 * line_w))/(rows/4);
		u += line_w;
		mod = fmod(u, rs + line_w);
		if(mod < line_w)
			return(texture->color2);
		return (texture->color1);
	}
	*/
}
