/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:06:16 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/09 23:09:01 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "vector.h"
#include "mlx.h"

static t_vec2i	set_vec2i(int x, int y)
{
	t_vec2i v;

	v.x = x;
	v.y = y;
	return (v);
}

static void		draw_l(t_mlx *mlx, t_vec2i p0, t_vec2i p1, int color)
{
	t_vec2i	p;
	t_vec2i	d;
	int		yi;
	int		delta;

	d = set_vec2i(p1.x - p0.x, p1.y - p0.y);
	yi = 1;
	if (d.y < 0)
	{
		yi = -1;
		d.y = -d.y;
	}
	delta = 2 * d.y - d.x;
	p = set_vec2i(p0.x, p0.y);
	while (p.x < p1.x)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, p.x, p.y, color);
		if (delta > 0)
		{
			p.y = p.y + yi;
			delta = delta - (2 * d.x);
		}
		delta = delta + (2 * d.y);
		p.x++;
	}
}

static void		draw_h(t_mlx *mlx, t_vec2i p0, t_vec2i p1, int color)
{
	t_vec2i		p;
	t_vec2i		d;
	int			xi;
	int			delta;

	d = set_vec2i(p1.x - p0.x, p1.y - p0.y);
	xi = 1;
	if (d.x < 0)
	{
		xi = -1;
		d.x = -d.x;
	}
	delta = 2 * d.x - d.y;
	p = set_vec2i(p0.x, p0.y);
	while (p.y < p1.y)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, p.x, p.y, color);
		if (delta > 0)
		{
			p.x = p.x + xi;
			delta = delta - (2 * d.y);
		}
		delta = delta + (2 * d.x);
		p.y++;
	}
}

void			draw_line(t_mlx *mlx, t_vec2i p0, t_vec2i p1, int color)
{
	if (ft_abs(p1.y - p0.y) < ft_abs(p1.x - p0.x))
	{
		if (p0.x > p1.x)
			draw_l(mlx, p1, p0, color);
		else
			draw_l(mlx, p0, p1, color);
	}
	else
	{
		if (p0.y > p1.y)
			draw_h(mlx, p1, p0, color);
		else
			draw_h(mlx, p0, p1, color);
	}
}
