/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:24:54 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/13 18:46:43 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"

t_vec3	calc_hit_normal_plane(t_shape *plane, t_raycast_hit *hit)
{
	hit = 0;
	return (ft_normalize_vec3(ft_sub_vec3(plane->target, plane->position)));
}

int		intersects_plane(t_ray *ray, t_shape *plane, t_raycast_hit *hit)
{
	double d;
	t_vec3 normal;

	normal = ft_normalize_vec3(ft_sub_vec3(plane->target, plane->position));
	d = ft_dot_vec3(ray->direction, normal);
	if (d > EPSILON)
		return (FALSE);
	hit->t = ft_dot_vec3(ft_sub_vec3(plane->position, ray->origin), normal) / d;
	if (hit->t > MIN_CLIP && hit->t < MAX_CLIP)
	{
		hit->distance = hit->t;
		hit->point = point_on_ray(ray, hit->t);
		hit->shape = plane;
		hit->normal = normal;
		return (TRUE);
	}
	return (FALSE);
}
