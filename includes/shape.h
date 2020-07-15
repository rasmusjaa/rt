/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:22:43 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/14 19:04:00 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

#include "rt.h"

typedef struct	s_quadratic
{
	double		a;
	double		b;
	double		c;
}				t_quadratic;

int		intersects_shape(t_ray *ray, t_shape *shape, t_raycast_hit *hit, int debug);
int		intersects_sphere(t_ray *ray, t_shape *sphere, t_raycast_hit *hit);
int		intersects_plane(t_ray *ray, t_shape *plane, t_raycast_hit *hit);
int		intersects_cone(t_ray *ray, t_shape *cone, t_raycast_hit *hit);
int		intersects_cylinder(t_ray *ray, t_shape *cyl, t_raycast_hit *hit);
int		intersects_triangle(t_ray *ray, t_triface *triface, t_raycast_hit *hit);
int		intersects_bounds(t_ray *ray, t_bounds *b, int debug);
int		intersects_model(t_ray *ray, t_shape *model, t_raycast_hit *hit, int debug);
int		intersects_octree_model(t_ray *ray, t_shape *model, t_octree *node, t_raycast_hit *hit, int debug);

t_vec3	calc_hit_normal(t_raycast_hit *hit);
t_vec3	calc_hit_normal_sphere(t_shape *sphere, t_raycast_hit *hit);
t_vec3	calc_hit_normal_plane(t_shape *plane, t_raycast_hit *hit);
t_vec3	calc_hit_normal_cone(t_shape *cone, t_raycast_hit *hit);
t_vec3	calc_hit_normal_cylinder(t_shape *c, t_raycast_hit *hit);

t_vec3	point_on_ray(t_ray *r, double t);
int		solve_quadratic(t_quadratic q, double *t1, double *t2);

#endif
