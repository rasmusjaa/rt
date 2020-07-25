/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 12:53:20 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/25 13:41:50 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_image.h"
#include "libft.h"

static t_cube_map_face determine_face(t_vec3 v)
{
	if (ft_abs_d(v.x) > ft_abs_d(v.y))
	{
		if (ft_abs_d(v.x) > ft_abs_d(v.z))
		{
			if (v.x < 0)
				return (LEFT);
			else
				return (RIGHT);
		}
		else 
			return (FRONT);
	}
	else
	{
		if (ft_abs_d(v.y) > ft_abs_d(v.z))
		{
			if (v.y < 0)
				return (BOTTOM);
			else
				return (TOP);
			// c = ft_make_vec3(v.x, v.z, v.y); // top bottom
		}
		else
			return (BACK);
	}
	return (FRONT);
}

t_rgba sample_cube_map(t_mlx_img *cube_map, t_vec3 v)
{
	int dir = determine_face(v);
	t_vec3 c;

	if (dir == FRONT || dir == BACK)
		c = ft_make_vec3(v.x, v.y, v.z);
	else if (dir == LEFT || dir == RIGHT)
		c = ft_make_vec3(v.z, v.y, v.x);
	else if (dir == TOP || dir == BOTTOM)
		c = ft_make_vec3(v.x, v.z, v.y);
	
	c.x = (c.x / ft_abs_d(c.z)) + 1.0;
	c.y = -(c.y / ft_abs_d(c.z)) + 1.0;

	if (dir == FRONT)
	{
		c.x += 2.0;
		c.y += 2.0;
	}
	else if (dir == BACK)
	{
		c.x += 4.0;
		c.y += 2.0;
	}
	else if (dir == LEFT)
	{
		// c.x += 2.0;
		c.y += 2.0;
	}
	else if (dir == RIGHT)
	{
		c.x += 4.0;
		c.y += 2.0;
	}
	else if (dir == BOTTOM)
	{
		c.x += 2.0;
		c.y += 4.0;
	}
	else if (dir == TOP)
	{
		c.x += 2.0;
		c.y += 0.0;
	}

	int color = get_pixel_mlx_img(cube_map, c.x/8.0 * cube_map->width, c.y/6.0 * cube_map->height);
	t_rgba rgba = ft_make_rgba(
		(double)((color >> (16)) & 0xff) / 255.0,
		(double)((color >> (8)) & 0xff) / 255.0,
		(double)((color >> (0)) & 0xff) / 255.0,
		1.0);
	return (rgba);
}
