/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 12:53:20 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 14:31:51 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_image.h"
#include "libft.h"

static t_cube_map_face	determine_face2(t_vec3 v)
{
	if (ft_abs_d(v.y) > ft_abs_d(v.z))
	{
		if (v.y < 0)
			return (BOTTOM);
		else
			return (TOP);
	}
	else
	{
		if (v.z < 0)
			return (FRONT);
		else
			return (BACK);
	}
	return (FRONT);
}

static t_cube_map_face	determine_face(t_vec3 v)
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
		{
			if (v.z < 0)
				return (FRONT);
			else
				return (BACK);
		}
	}
	else
		return (determine_face2(v));
}

static t_vec3			set_map_axis(t_cube_map_face dir, t_vec3 v)
{
	t_vec3	c;

	c = ft_make_vec3(0, 0, 1);
	if (dir == FRONT)
		c = ft_make_vec3(v.x, v.y, v.z);
	else if (dir == BACK)
		c = ft_make_vec3(-v.x, v.y, v.z);
	else if (dir == LEFT)
		c = ft_make_vec3(-v.z, v.y, v.x);
	else if (dir == RIGHT)
		c = ft_make_vec3(v.z, v.y, v.x);
	else if (dir == TOP)
		c = ft_make_vec3(v.x, v.z, v.y);
	else if (dir == BOTTOM)
		c = ft_make_vec3(v.x, -v.z, v.y);
	return (c);
}

/*
** Samples a cube map using a directional vector
** This could be a camera ray direction or reflection vector.
** Assumes vector is normalized.
*/

t_rgba					sample_cube_map(t_mlx_img *cube_map, t_vec3 v)
{
	int		dir;
	t_vec3	c;

	dir = determine_face(v);
	c = set_map_axis(dir, v);
	c.x = (c.x / ft_abs_d(c.z)) + 1.0;
	c.y = -(c.y / ft_abs_d(c.z)) + 1.0;
	if (dir == FRONT)
		c = ft_make_vec3(c.x + 2.0, c.y + 2.0, c.z);
	else if (dir == BACK)
		c = ft_make_vec3(c.x + 6.0, c.y + 2.0, c.z);
	else if (dir == LEFT)
		c = ft_make_vec3(c.x, c.y + 2.0, c.z);
	else if (dir == RIGHT)
		c = ft_make_vec3(c.x + 4.0, c.y + 2.0, c.z);
	else if (dir == BOTTOM)
		c = ft_make_vec3(c.x + 2.0, c.y + 4.0, c.z);
	else if (dir == TOP)
		c = ft_make_vec3(c.x + 2.0, c.y, c.z);
	return (ft_get_rgba(get_pixel_mlx_img(cube_map, (c.x / 8.0) *
		cube_map->width, (c.y / 6.0) * cube_map->height)));
}
