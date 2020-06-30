/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:46:47 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/30 11:42:02 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef struct	s_quadratic
{
	double		a;
	double		b;
	double		c;
}				t_quadratic;

t_vec3	point_on_ray(t_ray *r, double t)
{
	t_vec3 p;

	p = ft_add_vec3(r->origin, ft_mul_vec3(r->direction, t));
	return (p);
}

int			solve_quadratic(t_quadratic q, double *t1, double *t2)
{
	double d;

	*t1 = -1;
	*t2 = -1;
	d = q.b * q.b - 4 * q.a * q.c;
	if (d == 0)
	{
		*t1 = (-q.b - sqrt(d)) / (2.0 * q.a);
		return (1);
	}
	if (d > 0)
	{
		*t1 = (-q.b - sqrt(d)) / (2.0 * q.a);
		*t2 = (-q.b + sqrt(d)) / (2.0 * q.a);
		return (2);
	}
	return (0);
}

int	intersects_sphere(t_ray *ray, t_shape *sphere, t_raycast_hit *hit)
{
	t_quadratic	q;
	t_vec3		oc;
	int 		hits;

	oc = ft_sub_vec3(ray->origin, sphere->position);
	q.a = ft_dot_vec3(ray->direction, ray->direction);
	q.b = 2.0 * ft_dot_vec3(oc, ray->direction);
	q.c = ft_dot_vec3(oc, oc) - (sphere->radius * sphere->radius);
	hits = solve_quadratic(q, &hit->t, &hit->t2);
	if (hits > 0)
	{
		if ((hit->t > hit->t2 || hit->t < MIN_CLIP) && hit->t2 > MIN_CLIP)
			ft_swap_d(&hit->t, &hit->t2);
		if (hit->t > MAX_CLIP || hit->t < MIN_CLIP)
			return (FALSE);
		hit->point = point_on_ray(ray, hit->t);
		hit->distance = hit->t;
		return (TRUE);
	}
	return (FALSE);
}

int	intersects_plane(t_ray *ray, t_shape *plane, t_raycast_hit *hit)
{
	double d;
	t_vec3 normal;

	normal = ft_normalize_vec3(ft_sub_vec3(plane->position, plane->target));
	d = ft_dot_vec3(ray->direction, normal);
	if (d < EPSILON)
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

int	intersects_cone(t_ray *ray, t_shape *cone, t_raycast_hit *hit)
{
	t_quadratic	q;
	t_vec3		oc;			// cone position to ray origin
	t_vec3		v;			// cone direction
	double		theta_sqr;

	theta_sqr = ft_deg_to_rad(cone->angle) * ft_deg_to_rad(cone->angle);

	v = ft_normalize_vec3(ft_sub_vec3(cone->target, cone->position));
	oc = ft_sub_vec3(ray->origin, cone->position);
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
		hit->distance = hit->t;
		// hit->normal = calc_cone_normal(cone, hit);
		if ((ft_dot_vec3(
				ft_sub_vec3(hit->point, cone->position), v) < 0))
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

int	intersects_cylinder(t_ray *ray, t_shape *cyl, t_raycast_hit *hit)
{
	t_quadratic	q;
	t_vec3		v;		// cylinder direction
	t_vec3		ocxv;	// cross product of ray origin and cylinder direction
	t_vec3		dxv;	// cross product of ray direction and cylinder direction

	v = ft_sub_vec3(cyl->position, cyl->target);
	ocxv = ft_cross_vec3(ft_sub_vec3(ray->origin, cyl->position), v);
	dxv = ft_cross_vec3(ray->direction, v);
	q.a = ft_dot_vec3(dxv, dxv);
	q.b = 2 * ft_dot_vec3(dxv, ocxv);
	q.c = ft_dot_vec3(ocxv, ocxv) - ((cyl->radius * cyl->radius) *
		ft_dot_vec3(v, v));
	if (solve_quadratic(q, &hit->t, &hit->t2))
	{
		if (hit->t < 0 || (hit->t2 > 0 && hit->t2 < hit->t))
			hit->t = hit->t2;
		if (hit->t < 0 || hit->t > MAX_CLIP)
			return (FALSE);
		hit->point = point_on_ray(ray, hit->t);
		hit->distance = hit->t;
		// hit->normal = calc_cylinder_normal(cyl, hit);
		return (TRUE);
	}
	return (FALSE);

}

int	intersects_shape(t_ray *ray, t_shape *shape, t_raycast_hit *hit)
{
	if ((shape->type == SPHERE && intersects_sphere(ray, shape, hit))
	|| (shape->type == PLANE && intersects_plane(ray, shape, hit))
	|| (shape->type == CONE && intersects_cone(ray, shape, hit))
	|| (shape->type == CYLINDER && intersects_cylinder(ray, shape, hit)))
	{
		hit->shape = shape;
		return (TRUE);
	}
	return (FALSE);
}
