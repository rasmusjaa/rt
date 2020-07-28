/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:24:54 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/28 21:54:25 by wkorande         ###   ########.fr       */
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
	
	p = hit->point;
	//p = ft_rotate_vec3(hit.point, ft_invert_vec3(plane->rotation));
	uv.x = ft_abs_d(hit->point.x) / plane->material->u_scale;
	uv.y = ft_abs_d(hit->point.z) / plane->material->v_scale;
	
	uv.x = uv.x - floor(uv.x);
	uv.y = uv.y - floor(uv.y);
	if (p.z < 0)
		uv.x = 1 - uv.x;
	if (p.x < 0)
		uv.y = 1 - uv.y;
	return (uv);
}

int		intersects_plane(t_ray *ray, t_shape *plane, t_raycast_hit *hit)
{
	double	d;
	t_vec3	temp;

	temp = plane->material->explode > EPSILON ? ft_add_vec3(plane->position, ft_mul_vec3(plane->target, plane->material->explode * ft_inv_lerp_d((double)rand(), 0, RAND_MAX)))  : plane->target;

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
