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

	int x0 = (int)x;
	int y0 = (int)y;
	int x1 = x0 + 1;
	int y1 = y0 + 1;
	double sx = x - (float)x0;
	double sy = y - (float)y0;
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

double octave_perlin(t_texture *texture, t_vec2 uv, int oct, double pers)
{
	double total = 0;
	double freq = 10;
	double amplitude = texture->settings.z;
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

// double ft_map(double v, double s1, double e1, double s2, double e2)
// {
// 	double r;
// 	double l1;
// 	double l2;
// 	double offset;

// 	l1 = e1 - s1;
// 	l2 = e2 - s2;
// 	offset = 0 - s1;
// 	r = (v + offset) / l1 * l2;
// 	return (r);
// }

// typedef struct s_data
// {
// 	void *mlx_ptr;
// 	void *mlx_win;
// }				t_data;

// int main()
// {
// 	t_data data;

// 	data.mlx_ptr = mlx_init();
// 	data.mlx_win = mlx_new_window(data.mlx_ptr, W, H, "hello");
// 	unsigned char ***g = create_gradient_vectors(); 
// 	for (int i = 0; i < H; i++)
// 	{
// 		for (int j = 0; j < W; j++)
// 		{
// 			float x = j / (float)(W);
// 			float y = i / (float)(H);
// 			double p = octave_perlin(x, y,1, 1, g);
// 			int col = p*255;
// 			int hex = (((col << 8 ) + col) << 8) + col;
// 			mlx_pixel_put(data.mlx_ptr, data.mlx_win, j, i, hex);
// 		}
// 	}
// 	delete_grad(g);
// 	mlx_hook(data.mlx_win,17, 0, escape, NULL);
// 	mlx_loop(data.mlx_ptr);
// 	return (0);
// }
