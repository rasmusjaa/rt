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

static double	surflet(double x, double y, double grad_x, double grad_y)
{
	double xy;

	xy = ft_smoothstep(x) * ft_smoothstep(y);
	return (xy * (grad_x * x + grad_y * y));
}

double			perlin_noise(t_perlin_data *perlin, double x, double y)
{
	double		result;
	t_vec2i		cell;
	int			hash;
	t_vec2i		grid;

	result = 0;
	cell.x = floor(x);
	cell.y = floor(y);
	grid.y = cell.y;
	while (grid.y <= cell.y + 1)
	{
		grid.x = cell.x;
		while (grid.x <= cell.x + 1)
		{
			hash = perlin->perm[(perlin->perm[grid.x & 255] + grid.y) & 255];
			result += surflet(x - grid.x, y - grid.y,
				perlin->grads_x[hash & 255], perlin->grads_y[hash & 255]);
			grid.x++;
		}
		grid.y++;
	}
	return (result);
}

double			o_perlin(t_texture *texture, t_vec2 uv, int oct, double pers)
{
	double	total;
	double	freq;
	double	maxvalue;
	double	amp;
	int		i;

	freq = ft_clamp_d(texture->settings.z, 5, 100);
	total = 0;
	i = 0;
	uv.x = uv.x * 2 - 1;
	uv.y = uv.y * 2 - 1;
	maxvalue = 0;
	amp = 5;
	while (i < oct)
	{
		total += perlin_noise(texture->perlin_data, uv.x *
			freq, uv.y * freq) * amp;
		maxvalue += amp;
		amp *= pers;
		freq *= 2;
		i++;
	}
	return ((total / maxvalue) / 2.0 + 0.5);
}
