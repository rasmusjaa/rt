/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:24:54 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/23 14:55:10 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "libft.h"

t_vec3	calc_hit_normal_plane(t_shape *plane, t_raycast_hit *hit)
{
	return (plane->target);
	hit = 0;
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
