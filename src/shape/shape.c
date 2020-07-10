/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:46:47 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/10 21:46:59 by wkorande         ###   ########.fr       */
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

	normal = ft_normalize_vec3(ft_sub_vec3(plane->target, plane->position));
	d = ft_dot_vec3(ray->direction, normal);
	if (d > EPSILON)
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
		if ((ft_dot_vec3(
				ft_sub_vec3(hit->point, cone->position), v) < 0))
			return (FALSE);
		hit->distance = hit->t;
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
		return (TRUE);
	}
	return (FALSE);

}

int intersects_triangle(t_ray *ray, t_triface *triface, t_raycast_hit *hit)
{
	t_vec3	p0;
	t_vec3	p1;
	t_vec3	p2;
	double	d;

	d = ft_dot_vec3(triface->normal, ray->direction);
	if (d > EPSILON)
		return (FALSE);
	hit->t = ft_dot_vec3(ft_sub_vec3(triface->v[0], ray->origin), triface->normal) / d;
	if (hit->t < 0)
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
		return (TRUE);
	}
	return (FALSE);
}

/*
** mesh bounds are calculated on load
** axis aligned
*/
int	intersects_bounds(t_ray *ray, t_bounds *b, int debug)
{
	double txmin = (b->min.x - ray->origin.x) / ray->direction.x;
	double txmax = (b->max.x - ray->origin.x) / ray->direction.x;

	// need to swap if we are looking from behind, as is only works if camera pos in front of bounds
	if (txmin > txmax)
		ft_swap_d(&txmin, &txmax);

	double tymin = (b->min.y - ray->origin.y) / ray->direction.y;
	double tymax = (b->max.y - ray->origin.y) / ray->direction.y;

	if (tymin > tymax)
		ft_swap_d(&tymin, &tymax);

	if ((txmin > tymax) || (tymin > txmax))
		return (FALSE);

	double tzmin = (b->min.z - ray->origin.z) / ray->direction.z;
	double tzmax = (b->max.z - ray->origin.z) / ray->direction.z;

	if (tzmin > tzmax)
		ft_swap_d(&tzmin, &tzmax);

	if ((txmin > tzmax) || (tzmin > txmax))
		return (FALSE);

	if ((tymin > tzmax)  || (tzmin > tymax))
		return (FALSE);
	if (debug)
		return (TRUE);
	return (TRUE);
}

t_vec3 calc_smooth_normal(t_triface *tf, t_vec3 p)
{
	t_vec3 n;

	double p0 = ft_len_vec3(ft_sub_vec3(p, tf->v[0]));
	double p1 = ft_len_vec3(ft_sub_vec3(p, tf->v[1]));
	double p2 = ft_len_vec3(ft_sub_vec3(p, tf->v[2]));

	n = ft_add_vec3(ft_mul_vec3(tf->n[0], p0), ft_add_vec3(ft_mul_vec3(tf->n[1], p1), ft_mul_vec3(tf->n[2], p2)));
	return (ft_normalize_vec3(n));
}

int intersects_octree_model(t_ray *ray, t_shape *model, t_octree *node, t_raycast_hit *hit, int debug)
{
	size_t i;
	t_raycast_hit cur_hit;
	double min_dist;
	int hit_found;

	if (!intersects_bounds(ray, &(node->bounds), debug))
		return (FALSE);

	t_raycast_hit temp_hit;
	temp_hit.distance = MAX_CLIP;

	hit_found = FALSE;
	if (!node->is_last)
	{
		i = 0;
		while (i < NUM_CHILDREN)
		{
			if (intersects_octree_model(ray, model, node->children[i], &cur_hit, debug) && cur_hit.distance < temp_hit.distance)
			{
				temp_hit = cur_hit;
				*hit = temp_hit;
				hit_found = TRUE;
			}
			i++;
		}
	}
	else
	{
		if (debug)
			ft_printf("last\n");
		min_dist = MAX_CLIP;
		i = 0;
		while (i < node->num_tris)
		{
			if (intersects_triangle(ray, &(node->contains_trifaces[i]), &cur_hit))
			{
				hit_found = TRUE;
				if (cur_hit.distance < min_dist)
				{
					min_dist = cur_hit.distance;
					cur_hit.shape = model;
					*hit = cur_hit;
					hit->normal = calc_smooth_normal(&node->contains_trifaces[i], cur_hit.point); // cur_hit.normal;
				}
			}
			i++;
		}
	}
	return (hit_found);
}



int intersects_model(t_ray *ray, t_shape *model, t_raycast_hit *hit, int debug)
{
	size_t i;
	t_raycast_hit cur_hit;
	double min_dist;
	int hit_found;

	if (!intersects_bounds(ray, &(model->mesh->bounds), debug))
		return (FALSE);
	// else
	// {
	// 	hit->shape = model;
	// 	return (TRUE);
	// }

	hit_found = FALSE;
	min_dist = MAX_CLIP;
	i = 0;
	while (i < model->mesh->num_trifaces)
	{
		if (intersects_triangle(ray, &(model->mesh->trifaces[i]), &cur_hit))
		{
			hit_found = TRUE;
			if (cur_hit.distance < min_dist)
			{
				min_dist = cur_hit.distance;
				*hit = cur_hit;
				hit->shape = model;
			}
		}
		i++;
	}
	return (hit_found);
}

int	intersects_shape(t_ray *ray, t_shape *shape, t_raycast_hit *hit, int debug)
{
	if ((shape->type == SPHERE && intersects_sphere(ray, shape, hit))
	|| (shape->type == PLANE && intersects_plane(ray, shape, hit))
	|| (shape->type == CONE && intersects_cone(ray, shape, hit))
	|| (shape->type == CYLINDER && intersects_cylinder(ray, shape, hit))
	|| (shape->type == MODEL && intersects_octree_model(ray, shape, shape->octree, hit, debug)))
	{
		if (debug)
				ft_printf("hit shape, hit point %f %f %f\n", hit->point.x, hit->point.y, hit->point.z);
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
