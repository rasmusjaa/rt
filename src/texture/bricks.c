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
	int		rows 			= (int)texture->settings.x;
	double	mort_scale 		= texture->settings.y;
	double	section_height 	= 1 / (double)rows;
	double	brick_height 	= section_height / (1 + mort_scale);
	double	mort_height 	= brick_height * mort_scale;

	double brick_width = brick_height * 3.333333;
	
	if (fmod(v, section_height) < mort_height)
		return (texture->color2);
	if (fmod(v, section_height * 2) < section_height)
	{
		if (fmod(u, brick_width + mort_height) < mort_height)
			return (texture->color2);
		return (texture->color1);
	}
	else
	{
		if (fmod(u + (mort_height + brick_width) / 2, brick_width + mort_height) < mort_height)
			return (texture->color2);
		return (texture->color1);
	}
}
