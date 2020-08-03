/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 17:31:31 by sluhtala          #+#    #+#             */
/*   Updated: 2020/07/28 14:56:08 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "libft.h"

static double dotgrad(int ix, int iy, double x, double y, unsigned char ***g)
{
	double dx;
	double dy;
	double xvalue;
	double yvalue;

	dx = x - (double)ix;
    dy = y - (double)iy;
	ix = ix % GRAD_MAX;
	iy = iy % GRAD_MAX;
	xvalue = (float)g[iy][ix][0] / 122.5 - 1;
	yvalue = (float)g[iy][ix][1] / 122.5 - 1;

	return (dx * xvalue + dy * yvalue);
}


double	perlin_noise(t_texture *texture, double x, double y)
{
	x = fmod(x, GRAD_MAX);
	y = fmod(y, GRAD_MAX);
	int x0 = (int)x;
	int y0 = (int)y;
	int x1 = x0 + 1;
	int y1 = y0 + 1;
	double sx = x - x0;
	double sy = y - y0;
	double n0, n1, ix0, ix1, value;

	n0 = dotgrad(x0, y0, x, y, texture->grad_vectors);
	n1 = dotgrad(x1, y0, x, y, texture->grad_vectors);
	ix0 = ft_lerp_d(n0, n1, sx);
	n0 = dotgrad(x0, y1, x, y, texture->grad_vectors);
	n1 = dotgrad(x1, y1, x, y, texture->grad_vectors);
	ix1 = ft_lerp_d(n0, n1, sx);
	value = ft_lerp_d(ix0, ix1, sy);
	return (value / 2 + 0.5);
}

double o_perlin(t_texture *texture, t_vec2 uv, int oct, double pers)
{
	double total = 0;
	double freq = texture->settings.z;
	double amplitude = 1;
	double maxvalue = 0;

	for (int i = 0; i < oct; i++)
	{
		total += perlin_noise(texture, uv.x * freq, uv.y * freq) * amplitude;
		maxvalue += amplitude;
		amplitude *= pers;
		freq *= 2;
	}
	return (total / maxvalue);
}

