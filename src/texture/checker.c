/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:01:24 by sluhtala          #+#    #+#             */
/*   Updated: 2020/08/04 14:39:06 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "libft.h"

t_rgba	checker_texture(t_texture *texture, double v, double u)
{
	float	size;
	t_rgba	col1;
	t_rgba	col2;

	size = ft_clamp_d(texture->settings.x, 0.001, 1000);
	col1 = texture->color1;
	col2 = texture->color2;
	if (fmod(u, size * 2) < size)
	{
		if (fmod(v, size * 2) < size)
			return (col1);
		else
			return (col2);
	}
	else
	{
		if (fmod(v, size * 2) < size)
			return (col2);
		else
			return (col1);
	}
	return (ft_make_rgba(0, 0, 0, 1));
}
