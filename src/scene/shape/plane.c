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
	t_vec3 	rrotate;
	p = hit->point;
	
	rrotate = ft_invert_vec3(plane->rotation);

	p = ft_sub_vec3(p, plane->position);
	if (rrotate.z)
	p = ft_rotate_vec3(hit->point, ft_make_vec3(0,0, rrotate.z));
	if (rrotate.y)
	p = ft_rotate_vec3(hit->point, ft_make_vec3(0,rrotate.y,0));
	if (rrotate.x)
	p = ft_rotate_vec3(hit->point, ft_make_vec3(rrotate.x, 0, 0));
	
	uv.x = (p.x) / plane->material->u_scale;
	uv.y = (p.z) / plane->material->v_scale;
	
	uv.x = uv.x - floor(uv.x);
	uv.y = uv.y - floor(uv.y);

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
