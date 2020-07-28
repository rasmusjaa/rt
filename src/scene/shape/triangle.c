/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:38:15 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/28 18:59:58 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "libft.h"

t_vec2 calc_hit_uv_triangle(t_triface *triface, t_raycast_hit *hit)
{
	t_vec2 uv;
	double u;
	double v;
	double w;

	u = ft_len_vec3(ft_cross_vec3(ft_sub_vec3(hit->point, triface->v[0]), ft_sub_vec3(triface->v[2], triface->v[0]))) * 0.5;
	v = ft_len_vec3(ft_cross_vec3(ft_sub_vec3(hit->point, triface->v[1]), ft_sub_vec3(triface->v[2], triface->v[1]))) * 0.5;
	w = 1.0 - u - v;
	uv = ft_add_vec2(ft_mul_vec2(triface->uv[0], u), ft_add_vec2(ft_mul_vec2(triface->uv[1], v), ft_mul_vec2(triface->uv[2], w)));
	uv.x -= floor(uv.x);
	uv.y -= floor(uv.y);
	return (uv);
}

int intersects_triangle(t_ray *ray, t_triface *triface, t_raycast_hit *hit)
{
	t_vec3	p0;
	t_vec3	p1;
	t_vec3	p2;
	double	d;

	d = ft_dot_vec3(triface->normal, ray->direction);
	if (ft_abs_d(d) < EPSILON)
		return (FALSE);
	hit->t = ft_dot_vec3(ft_sub_vec3(triface->v[0], ray->origin), triface->normal) / d;
	if (hit->t < MIN_CLIP || hit->t > MAX_CLIP)
		return (FALSE);
	hit->point = ft_add_vec3(ray->origin, ft_mul_vec3(ray->direction, hit->t));

	p0 = ft_sub_vec3(hit->point, triface->v[0]);
	p1 = ft_sub_vec3(hit->point, triface->v[1]);
	p2 = ft_sub_vec3(hit->point, triface->v[2]);

	if (ft_dot_vec3(triface->normal, ft_cross_vec3(triface->e[0], p0)) >= 0 &&
		ft_dot_vec3(triface->normal, ft_cross_vec3(triface->e[1], p1)) >= 0 &&
		ft_dot_vec3(triface->normal, ft_cross_vec3(triface->e[2], p2)) >= 0)
	{
		hit->distance = hit->t;
		hit->normal = triface->normal;
		hit->triface = triface;
		return (TRUE);
	}
	return (FALSE);
}
