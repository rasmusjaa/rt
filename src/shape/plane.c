/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:24:54 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/16 18:04:29 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"

t_vec3	calc_hit_normal_plane(t_shape *plane, t_raycast_hit *hit)
{
	return (plane->normal);
	hit = 0;
}

int		intersects_plane(t_ray *ray, t_shape *plane, t_raycast_hit *hit)
{
	double d;

	d = ft_dot_vec3(ray->direction, plane->normal);
	if (ft_abs_d(d) < EPSILON)
		return (FALSE);
	hit->t = ft_dot_vec3(ft_sub_vec3(plane->position, ray->origin), plane->normal) / d;
	if (hit->t > MIN_CLIP && hit->t < MAX_CLIP)
	{
		hit->distance = hit->t;
		hit->point = point_on_ray(ray, hit->t);
		hit->shape = plane;
		hit->normal = plane->normal;
		return (TRUE);
	}
	return (FALSE);
}

t_vec3	calc_plane_normal(t_vec3 position, t_vec3 target)
{
	t_vec3	normal;

	if (position.x == target.x && position.y == target.y &&
		position.z == target.z)
		target.y = position.y + 1;
	normal = ft_sub_vec3(target, position);
	normal = ft_normalize_vec3(normal);
	return (normal);
}
