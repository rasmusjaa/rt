/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:24:54 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/30 16:37:29 by sluhtala         ###   ########.fr       */
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
	t_vec2		uv;
	t_vec3	p;
	t_vec3 n = hit->normal;
	t_vec3 u = ft_normalize_vec3(ft_make_vec3(n.y, -n.x, 0));
	t_vec3 v;

//	t_vec3 	rrotate;
	p = hit->point;

	p = ft_sub_vec3(p, plane->position);
	if (n.x == 0 && n.y == 0)
	{
		ft_normalize_vec3(ft_make_vec3(n.y, -n.x, n.z));
	}
		v = ft_cross_vec3(n, u);
		uv.x = ft_dot_vec3(u, p);
		uv.y = ft_dot_vec3(v, p);
	
		uv.x /= plane->material->u_scale;
		uv.y /= plane->material->v_scale;	

		double angle = ft_deg_to_rad(plane->rotation.y);
		double ru = uv.x * cos(angle) - uv.y * sin(angle);
		double rv = uv.y * cos(angle) + uv.x * sin(angle);

		uv.x = ru - floor(ru);
		uv.y = rv - floor(rv);

	return (uv);
}

int		intersects_plane(t_ray *ray, t_shape *plane, t_raycast_hit *hit)
{
	double	d;
	t_vec3	temp;

	temp = plane->material->explode > EPSILON ? ft_add_vec3(plane->position, ft_mul_vec3(plane->target, plane->material->explode * ft_inv_lerp_d((double)rand(), 0, RAND_MAX)))  : plane->position;

	d = ft_dot_vec3(ray->direction, plane->target);
	if (ft_abs_d(d) < EPSILON)
		return (FALSE);
	hit->t = ft_dot_vec3(ft_sub_vec3(temp, ray->origin), plane->target) / d;
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
