/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 17:31:31 by sluhtala          #+#    #+#             */
/*   Updated: 2020/08/04 15:56:21 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "libft.h"

static double	ft_smoothstep(double x)
{
	double y;

	x = fabs(x);
	if (x >= 1.0)
		return (0);
	y = 1.0 - (3.0 - 2.0 * x) * x * x;
	return (y);
}

static double surflet(double x, double y, double grad_x, double grad_y)
{
	double xy;

	xy = ft_smoothstep(x) * ft_smoothstep(y);
	return (xy * (grad_x * x + grad_y * y));
}

double perlin_noise(t_perlin_data *perlin, double x, double y)
{
	double		result;
	t_vec2i		cell;
	int			hash;
	t_vec2i		grid;

	result = 0;
	cell.x = floor(x);
	cell.y = floor(y);
	grid.y = cell.y;
	grid.x = cell.x;
	while (grid.y <= cell.y + 1)
	{
		while (grid.x <= cell.x + 1)
		{
			hash = perlin->perm[(perlin->perm[grid.x & 255] + grid.y) & 255];
			result += surflet(x - grid.x, y - grid.y, perlin->grads_x[hash & 255],
				perlin->grads_y[hash & 255]);
			grid.x++;
		}
		grid.y++;
	}
	return (result);
}

/*
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
*/
double o_perlin(t_texture *texture, t_vec2 uv, int oct, double pers)
{
	double total = 0;
	double freq = ft_clamp_d(texture->settings.z, 0.001, 1000);
	double amplitude = 1;
	double maxvalue = 0;

	double x = 255 / uv.x;
	double y = 255 / uv.y;
	return (perlin_noise(texture->perlin_data, x, y));
	for (int i = 0; i < oct; i++)
	{
		total += perlin_noise(texture->perlin_data, x * freq, y * freq) * amplitude;
		maxvalue += amplitude;
		amplitude *= pers;
		freq *= 2;
	}
	return (total / maxvalue);
}

