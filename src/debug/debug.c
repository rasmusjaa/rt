/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 11:39:28 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 14:04:47 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "rt.h"
#include "ft_printf.h"
#include "vector.h"
#include "octree.h"
#include "shape.h"
#include "scene.h"

void	print_vec3(char *s, t_vec3 v)
{
	ft_printf("%s %.2f, %.2f, %.2f\n", s, v.x, v.y, v.z);
}

void	print_rgba(char *s, t_rgba c)
{
	ft_printf("%s %.2f, %.2f, %.2f %.2f\n", s, c.r, c.g, c.b, c.a);
}

t_vec2i	world_to_screen_point(t_camera *camera, t_vec3 world_point,
			t_vec2i window_size)
{
	t_vec3	dir;
	t_vec2i	screen_point;

	dir = ft_normalize_vec3(ft_sub_vec3(world_point, camera->position));
	screen_point.x = (dir.x + 0.5) * window_size.x;
	screen_point.y = window_size.y - ((dir.y + 0.5) * window_size.y);
	return (screen_point);
}
