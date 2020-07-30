/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:46:47 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/30 17:17:20 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "raycast.h"
#include "shape.h"
#include "mesh.h"
#include "ft_printf.h"

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



int	intersects_shape(t_ray *ray, t_shape *shape, t_raycast_hit *hit, int debug)
{
	if (shape->bounds.active && !intersects_bounds(ray, &shape->bounds, debug))
		return(FALSE);
	if ((shape->type == SPHERE && intersects_sphere(ray, shape, hit))
	|| (shape->type == PLANE && intersects_plane(ray, shape, hit))
	|| (shape->type == CONE && intersects_cone(ray, shape, hit))
	|| (shape->type == CYLINDER && intersects_cylinder(ray, shape, hit))
	|| (shape->type == MODEL && intersects_octree_model(ray, shape, shape->octree, hit, debug)))
	{
		if (shape->bounds.active && !point_inside_bounds(hit->point, shape))
			return (FALSE);
		if (debug)
				ft_printf("hit shape type %d, hit point %f %f %f\n", shape->type, hit->point.x, hit->point.y, hit->point.z);
		hit->shape = shape;
		return (TRUE);
	}
	return (FALSE);
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
	else if (hit->shape->type == MODEL)
		return hit->normal;
	else
	{
		ft_printf("calc_hit_normal -- unknown shape type\n");
		return (ft_make_vec3(0, 0, 0));
	}
}

t_vec2 calc_hit_uv(t_raycast_hit *hit)
{
	if (!hit->shape)
	{
		ft_printf("calc_hit_uv -- hit.shape is null!\n");
		return (ft_make_vec2(0, 0));
	}
	if (hit->shape->type == SPHERE)
		return (calc_hit_uv_sphere(hit->shape, hit));
	else if (hit->shape->type == PLANE)
		return (calc_hit_uv_plane(hit->shape, hit));
	else if (hit->shape->type == CONE)
		return (calc_hit_uv_cone(hit->shape, hit));
	else if (hit->shape->type == CYLINDER)
		return (calc_hit_uv_cylinder(hit->shape, hit));
	else if (hit->shape->type == MODEL)
		return (calc_hit_uv_triangle(hit->shape, hit));
	else
	{
		ft_printf("calc_hit_uv -- unknown shape type\n");
		return (ft_make_vec2(0, 0));
	}
}
