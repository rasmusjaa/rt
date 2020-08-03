/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:38:15 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 16:18:02 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "libft.h"
#include "raycast.h"

t_vec3	calc_hit_normal_triangle(t_triface *triface, t_raycast_hit *hit)
{
	t_vec3 n;
	double u;
	double v;
	double w;

	u = ft_len_vec3(ft_cross_vec3(ft_sub_vec3(hit->point, triface->v[0]),
		ft_sub_vec3(triface->v[2], triface->v[0]))) * 0.5;
	v = ft_len_vec3(ft_cross_vec3(ft_sub_vec3(hit->point, triface->v[1]),
		ft_sub_vec3(triface->v[2], triface->v[1]))) * 0.5;
	w = 1.0 - u - v;
	n = ft_div_vec3(ft_add_vec3(ft_mul_vec3(triface->n[0], u),
		ft_add_vec3(ft_mul_vec3(triface->n[1], v),
		ft_mul_vec3(triface->n[2], w))), 3);
	return (ft_normalize_vec3(n));
}

t_vec2	calc_hit_uv_triangle(t_shape *model, t_raycast_hit *hit)
{
	t_vec2	uv;
	double	a[4];
	t_vec3	p[3];

	p[0] = ft_sub_vec3(hit->triface->v[0], hit->point);
	p[1] = ft_sub_vec3(hit->triface->v[1], hit->point);
	p[2] = ft_sub_vec3(hit->triface->v[2], hit->point);
	a[0] = ft_len_vec3(ft_cross_vec3(ft_sub_vec3(hit->triface->v[0],
		hit->triface->v[1]), ft_sub_vec3(hit->triface->v[0],
		hit->triface->v[2])));
	a[1] = ft_len_vec3(ft_cross_vec3(p[1], p[2])) / a[0];
	a[2] = ft_len_vec3(ft_cross_vec3(p[2], p[0])) / a[0];
	a[3] = ft_len_vec3(ft_cross_vec3(p[0], p[1])) / a[0];
	uv = ft_add_vec2(ft_mul_vec2(hit->triface->uv[0], a[1]),
		ft_add_vec2(ft_mul_vec2(hit->triface->uv[1], a[2]),
		ft_mul_vec2(hit->triface->uv[2], a[3])));
	uv.y = 1.0 - uv.y;
	uv.x = fmod(uv.x / model->material->u_scale, 1.0);
	uv.y = fmod(uv.y / model->material->v_scale, 1.0);
	return (uv);
}

int		intersects_triangle(t_ray *ray, t_triface *triface, t_raycast_hit *hit)
{
	t_vec3	p[3];
	double	d;

	d = ft_dot_vec3(triface->normal, ray->direction);
	if (ft_abs_d(d) < EPSILON)
		return (FALSE);
	hit->t = ft_dot_vec3(ft_sub_vec3(triface->v[0], ray->origin),
		triface->normal) / d;
	if (hit->t < MIN_CLIP || hit->t > MAX_CLIP)
		return (FALSE);
	hit->point = ft_add_vec3(ray->origin, ft_mul_vec3(ray->direction, hit->t));
	p[0] = ft_sub_vec3(hit->point, triface->v[0]);
	p[1] = ft_sub_vec3(hit->point, triface->v[1]);
	p[2] = ft_sub_vec3(hit->point, triface->v[2]);
	if (ft_dot_vec3(triface->normal, ft_cross_vec3(triface->e[0], p[0])) >= 0 &&
		ft_dot_vec3(triface->normal, ft_cross_vec3(triface->e[1], p[1])) >= 0 &&
		ft_dot_vec3(triface->normal, ft_cross_vec3(triface->e[2], p[2])) >= 0)
	{
		hit->distance = hit->t;
		hit->normal = triface->normal;
		hit->triface = triface;
		return (TRUE);
	}
	return (FALSE);
}
