/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:27:12 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/28 21:54:13 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "libft.h"

t_vec3	calc_hit_normal_cone(t_shape *cone, t_raycast_hit *hit)
{
	t_vec3 n;
	t_vec3 cp;
	t_vec3 v;

	v = cone->target;
	cp = ft_sub_vec3(hit->point, cone->position);
	n = ft_sub_vec3(cp, ft_mul_vec3(v,
		(ft_len_vec3(cp) / cos(cone->radius))));
	return (ft_normalize_vec3(n));
}

t_vec2 calc_hit_uv_cone(t_shape *cone, t_raycast_hit *hit)
{
	cone = 0;
	hit = 0;
	return (ft_make_vec2(0,0));
}

int	intersects_cone(t_ray *ray, t_shape *cone, t_raycast_hit *hit)
{
	t_quadratic	q;
	t_vec3		oc;			// cone position to ray origin
	t_vec3		v;			// cone direction
	double		theta_sqr;
	t_vec3	temp;

	v = ft_sub_vec3(cone->target, cone->position);
	temp = cone->material->explode > EPSILON ? ft_add_vec3(cone->position, ft_mul_vec3(cone->target, cone->material->explode * ft_inv_lerp_d((double)rand(), 0, RAND_MAX)))  : v;


	theta_sqr = ft_deg_to_rad(cone->angle) * ft_deg_to_rad(cone->angle);

	// v = cone->target;
	oc = ft_sub_vec3(ray->origin, temp);
	q.a = ft_dot_vec3(ray->direction, v);
	q.a = ft_dot_vec3(ray->direction, ray->direction) -
		(1 + theta_sqr) * q.a * q.a;
	q.b = 2.0 * (ft_dot_vec3(ray->direction, oc) -
		(1 + theta_sqr)
		* ft_dot_vec3(ray->direction, v) * ft_dot_vec3(oc, v));
	q.c = ft_dot_vec3(oc, v);
	q.c = ft_dot_vec3(oc, oc) - (1 + theta_sqr) * q.c * q.c;
	if (solve_quadratic(q, &hit->t, &hit->t2) && (hit->t > 0) &&
		(hit->t < MAX_CLIP))
	{
		hit->point = point_on_ray(ray, hit->t);
		if ((ft_dot_vec3(
				ft_sub_vec3(hit->point, temp), v) < 0))
			return (FALSE);
		hit->distance = hit->t;
		return (TRUE);
	}
	return (FALSE);
}
