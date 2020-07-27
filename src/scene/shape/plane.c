/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:24:54 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/27 18:41:31 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "libft.h"
#include <math.h>

t_vec3	calc_hit_normal_plane(t_shape *plane, t_raycast_hit *hit)
{
	return (plane->target);
	hit = 0;
}

t_vec2 calc_hit_uv_plane(t_shape *plane, t_raycast_hit *hit)
{
	t_vec2 uv;
	//plane->material->u_scale...
	//
	plane = 0;	
	uv.x = ft_abs_d(hit->point.x) / 10;
	uv.y = ft_abs_d(hit->point.z) / 10;
	uv.x = fmod(uv.x, 1);
	uv.y = fmod(uv.y, 1);
	return (uv);
}

int		intersects_plane(t_ray *ray, t_shape *plane, t_raycast_hit *hit)
{
	double d;

	d = ft_dot_vec3(ray->direction, plane->target);
	if (ft_abs_d(d) < EPSILON)
		return (FALSE);
	hit->t = ft_dot_vec3(ft_sub_vec3(plane->position, ray->origin), plane->target) / d;
	if (hit->t > MIN_CLIP && hit->t < MAX_CLIP)
	{
		hit->distance = hit->t;
		hit->point = point_on_ray(ray, hit->t);
		hit->shape = plane;
		hit->normal = plane->target;
		return (TRUE);
	}
	return (FALSE);
}
