/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:46:47 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/05 19:55:50 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "mesh.h"

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

int intersects_triangle(t_ray *ray, t_triface *triface, t_raycast_hit *hit)
{
	// compute triangle normal (can be computed when loading mesh, as well as edges can be precomputed)
	// t_vec3 v0v1 = ft_sub_vec3(triface->v[1], triface->v[0]);
	// t_vec3 v0v2 = ft_sub_vec3(triface->v[2], triface->v[0]);
	triface->normal = triface->n[0]; //ft_normalize_vec3(ft_cross_vec3(v0v1, v0v2));

	// intersects triface plane? (plane intersection test using computed triface normal)
	double d = ft_dot_vec3(ray->direction, triface->normal);
	if (d < EPSILON)
		return (FALSE);
	double t = ft_dot_vec3(ft_sub_vec3(triface->v[0], ray->origin), triface->normal) / d;
	if (t < 0)
		return (FALSE);
	t_vec3 p = ft_add_vec3(ray->origin, ft_mul_vec3(ray->direction, t));

	// is intersection inside triface? (edges can be precomputed)
	t_vec3 e0 = ft_sub_vec3(triface->v[1], triface->v[0]);
	t_vec3 e1 = ft_sub_vec3(triface->v[2], triface->v[1]);
	t_vec3 e2 = ft_sub_vec3(triface->v[0], triface->v[2]);

	t_vec3 p0 = ft_sub_vec3(p, triface->v[0]);
	t_vec3 p1 = ft_sub_vec3(p, triface->v[1]);
	t_vec3 p2 = ft_sub_vec3(p, triface->v[2]);

	// dot product of triface normal and cross product of all need to be positive for p to be inside triface
	if (ft_dot_vec3(triface->normal, ft_cross_vec3(e0, p0)) >0 && ft_dot_vec3(triface->normal, ft_cross_vec3(e1, p1)) > 0 && ft_dot_vec3(triface->normal, ft_cross_vec3(e2, p2)) > 0)
	{
		hit->t = t;
		hit->distance = t;
		hit->point = p;
		return (TRUE);
	}
	return (FALSE);
}

int intersects_model(t_ray *ray, t_model *model, t_raycast_hit *hit)
{
	size_t i;

	// we should first check if ray intersects model bounds, then go through each triface

	i = 0;
	while (i < model->mesh->num_trifaces)
	{
		if (intersects_triangle(ray, &(model->mesh->trifaces[i]), hit))
		{
			hit->model = model;
			return (TRUE);
		}
		i++;
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

t_vec3 calc_hit_normal_sphere(t_shape *sphere, t_raycast_hit *hit)
{
	return (ft_normalize_vec3(ft_sub_vec3(hit->point, sphere->position)));
}

t_vec3 calc_hit_normal_plane(t_shape *plane, t_raycast_hit *hit)
{
	hit = 0;
	return (ft_normalize_vec3(ft_sub_vec3(plane->target, plane->position)));
}

t_vec3	calc_hit_normal_cone(t_shape *cone, t_raycast_hit *hit)
{
	t_vec3 n;
	t_vec3 cp;
	t_vec3 v;

	v = ft_normalize_vec3(ft_sub_vec3(cone->target, cone->position));
	cp = ft_sub_vec3(hit->point, cone->position);
	n = ft_sub_vec3(cp, ft_mul_vec3(v,
		(ft_len_vec3(cp) / cos(cone->radius))));
	return (ft_normalize_vec3(n));
}

t_vec3	calc_hit_normal_cylinder(t_shape *c, t_raycast_hit *hit)
{
	t_vec3 dir;
	t_vec3 c_to_hit;
	t_vec3 v;
	double d;

	dir = ft_normalize_vec3(ft_sub_vec3(c->target, c->position));
	c_to_hit = ft_sub_vec3(hit->point, c->position);
	d = ft_dot_vec3(dir, c_to_hit);
	v = ft_add_vec3(c->position, ft_mul_vec3(dir, d));
	return (ft_normalize_vec3(ft_sub_vec3(hit->point, v)));
}

t_vec3 calc_hit_normal(t_raycast_hit *hit)
{
	if (!hit->shape)
	{
		ft_printf("calc_hit_normal -- hit.shape is null!\n");
		return (ft_make_vec3(0, 0, 0));
	}
	if (hit->shape->type == SPHERE)
		return (calc_hit_normal_sphere(hit->shape, hit));
	else if (hit->shape->type == PLANE)
		return (calc_hit_normal_plane(hit->shape, hit));
	else if (hit->shape->type == CONE)
		return (calc_hit_normal_cone(hit->shape, hit));
	else if (hit->shape->type == CYLINDER)
		return (calc_hit_normal_cylinder(hit->shape, hit));
	else
	{
		ft_printf("calc_hit_normal -- unknown shape type\n");
		return (ft_make_vec3(0, 0, 0));
	}
}