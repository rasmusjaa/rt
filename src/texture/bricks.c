/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bricks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:48:47 by sluhtala          #+#    #+#             */
/*   Updated: 2020/08/04 14:40:03 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "libft.h"

t_rgba	brick_texture(t_texture *texture, double u, double v)
{
	double	mort_scale;
	double	section_height;
	double	brick_height;
	double	mort_height;

	mort_scale = texture->settings.y;
	section_height = 1 / ft_clamp_d(texture->settings.x, 1, 1000);
	brick_height = section_height / (1.0 + mort_scale);
	mort_height = brick_height * mort_scale;
	if (fmod(v, section_height) < mort_height)
		return (texture->color2);
	if (fmod(v, section_height * 2) < section_height)
	{
		if (fmod(u, brick_height * 3.33333 + mort_height) < mort_height)
			return (texture->color2);
		return (texture->color1);
	}
	else
	{
		if (fmod(u + (mort_height + brick_height * 3.33333) / 2, brick_height
				* 3.33333 + mort_height) < mort_height)
			return (texture->color2);
		return (texture->color1);
	}
}
