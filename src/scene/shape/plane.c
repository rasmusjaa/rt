/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:24:54 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/06 15:19:12 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "libft.h"
#include <math.h>
#include "raycast.h"

t_vec3	calc_hit_normal_plane(t_shape *plane, t_raycast_hit *hit)
{
	return (plane->target);
	hit = 0;
}

t_vec2	calc_hit_uv_plane(t_shape *plane, t_raycast_hit *hit)
{
	t_vec2	uv;
	t_vec3	p;
	t_vec3	n;
	t_vec3	u;
	double	temp[3];

	n = hit->normal;
	u = ft_normalize_vec3(ft_make_vec3(n.y, -n.x, 0));
	p = ft_sub_vec3(hit->point, plane->position);
	if (n.x == 0 && n.y == 0)
		u = ft_normalize_vec3(ft_make_vec3(n.y, -n.x, n.z));
	uv.x = ft_dot_vec3(u, p);
	uv.y = ft_dot_vec3(ft_cross_vec3(n, u), p);
	uv.x /= plane->material->u_scale;
	uv.y /= plane->material->v_scale;
	temp[0] = ft_deg_to_rad(plane->rotation.y);
	temp[1] = uv.x * cos(temp[0]) - uv.y * sin(temp[0]);
	temp[2] = uv.y * cos(temp[0]) + uv.x * sin(temp[0]);
	uv.x = temp[1] - floor(temp[1]);
	uv.y = temp[2] - floor(temp[2]);
	return (uv);
}

int		intersects_plane(t_ray *ray, t_shape *plane, t_raycast_hit *hit)
{
	double	d;
	t_vec3	temp;

	temp = plane->material->explode > EPSILON ? ft_add_vec3(plane->position,
		ft_mul_vec3(plane->target, plane->material->explode *
		ft_inv_lerp_d((double)rand(), 0, RAND_MAX))) : plane->position;
	d = ft_dot_vec3(ray->direction, plane->target);
	if (ft_abs_d(d) < EPSILON)
		return (FALSE);
	hit->t = ft_dot_vec3(ft_sub_vec3(temp, ray->origin), plane->target) / d;
	if (hit->t > MIN_CLIP && hit->t < MAX_CLIP)
	{
		hit->distance = hit->t;
		hit->point = point_on_ray(ray, hit->t);
		if (plane->radius > 0.001)
		{
			if (ft_len_vec3(ft_sub_vec3(hit->point, plane->position)) >
					plane->radius)
				return (FALSE);
		}
		hit->shape = plane;
		hit->normal = plane->target;
		return (TRUE);
	}
	return (FALSE);
}
