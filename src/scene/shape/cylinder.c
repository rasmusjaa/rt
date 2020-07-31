/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:29:03 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/28 21:54:19 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "libft.h"

t_vec3	calc_hit_normal_cylinder(t_shape *c, t_raycast_hit *hit)
{
	t_vec3 dir;
	t_vec3 c_to_hit;
	t_vec3 v;
	double d;

	dir = c->target;
	c_to_hit = ft_sub_vec3(hit->point, c->position);
	d = ft_dot_vec3(dir, c_to_hit);
	v = ft_add_vec3(c->position, ft_mul_vec3(dir, d));
	return (ft_normalize_vec3(ft_sub_vec3(hit->point, v)));
}

t_vec2 calc_hit_uv_cylinder(t_shape *cylinder, t_raycast_hit *hit)
{
	t_vec2 uv;
	t_vec3 n;
	t_vec3 p;
	double min;
	double max;

	min = 0;
	max = 1;
	p = ft_sub_vec3(hit->point, cylinder->position);
	n = ft_rotate_vec3(hit->normal, ft_invert_vec3(cylinder->rotation));
	uv.x = atan2(n.x, n.z) / (2.0 * M_PI) + 0.5;
    uv.y = (p.y - floor(p.y) - min) / (max - min);
	uv.x *= 6.0;
	uv.x /= cylinder->material->u_scale / cylinder->radius;
	uv.y /= cylinder->material->v_scale / cylinder->radius;
	return (uv);
}

int	intersects_cylinder(t_ray *ray, t_shape *cyl, t_raycast_hit *hit)
{
	t_quadratic	q;
	t_vec3		v;		// cylinder direction
	t_vec3		ocxv;	// cross product of ray origin and cylinder direction
	t_vec3		dxv;	// cross product of ray direction and cylinder direction
	double		temp;

	temp = cyl->material->explode > EPSILON ? cyl->radius + cyl->material->explode * ft_inv_lerp_d((double)rand(), 0, RAND_MAX) : cyl->radius;
	v = cyl->target;
	ocxv = ft_cross_vec3(ft_sub_vec3(ray->origin, cyl->position), v);
	dxv = ft_cross_vec3(ray->direction, v);
	q.a = ft_dot_vec3(dxv, dxv);
	q.b = 2 * ft_dot_vec3(dxv, ocxv);
	q.c = ft_dot_vec3(ocxv, ocxv) - ((temp * temp) *
		ft_dot_vec3(v, v));
	if (solve_quadratic(q, &hit->t, &hit->t2))
	{
		if (hit->t < 0 || (hit->t2 > 0 && hit->t2 < hit->t))
			hit->t = hit->t2;
		if (hit->t < 0 || hit->t > MAX_CLIP)
			return (FALSE);
		hit->point = point_on_ray(ray, hit->t);
		hit->distance = hit->t;
		return (TRUE);
	}
	return (FALSE);

}
