/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:22:43 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/24 17:46:57 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "rt.h"
# include "raycast.h"
# include "octree.h"
# include "color.h"
# include "vector.h"

typedef struct s_ray t_ray;
typedef struct s_raycast_hit t_raycast_hit;
typedef struct s_mesh t_mesh;
typedef struct s_triface t_triface;

typedef struct	s_quadratic
{
	double			a;
	double			b;
	double			c;
}				t_quadratic;

typedef enum	e_shape_type
{
	SPHERE,
	PLANE,
	CONE,
	CYLINDER,
	DISC,
	MODEL
}				t_shape_type;

typedef struct	s_shape_name_type_map
{
	char			name[20];
	t_shape_type	type;
}				t_shape_name_type_map;

typedef struct	s_shape
{
	char			*name;
	t_shape_type	type;
	t_vec3			position;
	t_vec3			target;
	t_vec3			rotation;
	double			scale;
	t_rgba			color;
	double			radius;
	double			angle;
	
	int				material_id;
	t_material		*material;
	double			opacity;
	double			reflection;
	double			refraction;
	double			shine;
	t_mesh			*mesh;
	t_octree		*octree;
}				t_shape;

int				intersects_shape(t_ray *ray, t_shape *shape,
					t_raycast_hit *hit, int debug);
int				intersects_sphere(t_ray *ray, t_shape *sphere,
					t_raycast_hit *hit);
int				intersects_plane(t_ray *ray, t_shape *plane,
					t_raycast_hit *hit);
int				intersects_cone(t_ray *ray, t_shape *cone,
					t_raycast_hit *hit);
int				intersects_cylinder(t_ray *ray, t_shape *cyl,
					t_raycast_hit *hit);
int				intersects_triangle(t_ray *ray, t_triface *triface,
					t_raycast_hit *hit);
int				intersects_bounds(t_ray *ray, t_bounds *b, int debug);
int				intersects_model(t_ray *ray, t_shape *model,
					t_raycast_hit *hit, int debug);
int				intersects_octree_model(t_ray *ray, t_shape *model,
					t_octree *node, t_raycast_hit *hit, int debug);

t_vec3			calc_hit_normal(t_raycast_hit *hit);
t_vec3			calc_hit_normal_sphere(t_shape *sphere, t_raycast_hit *hit);
t_vec3			calc_hit_normal_plane(t_shape *plane, t_raycast_hit *hit);
t_vec3			calc_hit_normal_cone(t_shape *cone, t_raycast_hit *hit);
t_vec3			calc_hit_normal_cylinder(t_shape *c, t_raycast_hit *hit);

t_vec3			point_on_ray(t_ray *r, double t);
int				solve_quadratic(t_quadratic q, double *t1, double *t2);

#endif
