/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:46:47 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/15 19:29:35 by rjaakonm         ###   ########.fr       */
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

	oc = ft_sub_vec3(ray->origin, sphere->position);
	q.a = ft_dot_vec3(ray->direction, ray->direction);
	q.b = 2.0 * ft_dot_vec3(oc, ray->direction);
	q.c = ft_dot_vec3(oc, oc) - (sphere->radius * sphere->radius);
	if (solve_quadratic(q, &hit->t, &hit->t2))
	{
		if (hit->t > hit->t2)
			ft_swap_d(&hit->t, &hit->t2);
		if (hit->t < 0)
		{
			hit->t = hit->t2;
			if (hit->t < 0)
				return (FALSE);
		}
		if (hit->t > MAX_COORD)
			return (FALSE);
		hit->point = point_on_ray(ray, hit->t);
		hit->normal = ft_normalize_vec3(ft_sub_vec3(hit->point, sphere->position));
		hit->shape = sphere;
		hit->distance = hit->t;
		return (TRUE);
	}
	return (FALSE);
}

int	intersects_shape(t_ray *ray, t_shape *shape, t_raycast_hit *hit)
{
	// select function from shape->type (function pointer?)
	if (shape->type == SPHERE)
	{
		if (intersects_sphere(ray, shape, hit))
		{
			// hit->shape = shape; // asetettu jo mut voi teha vaan tas jos haluu
			hit->color = shape->color;
			return (TRUE);
		}
	}
	// populate hit info
	return (FALSE);
}
