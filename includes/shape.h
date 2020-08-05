/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:22:43 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 13:03:35 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "rt.h"
# include "octree.h"
# include "color.h"
# include "vector.h"
# include "bounds.h"

struct s_mesh;
struct s_triface;
struct s_ray;
struct s_material;
struct s_octree;
struct s_raycast_hit;

typedef struct			s_quadratic
{
	double			a;
	double			b;
	double			c;
}						t_quadratic;

typedef enum			e_shape_type
{
	SPHERE,
	PLANE,
	CONE,
	CYLINDER,
	DISC,
	MODEL
}						t_shape_type;

typedef struct			s_shape_name_type_map
{
	char				name[20];
	t_shape_type		type;
}						t_shape_name_type_map;

typedef struct			s_shape
{
	char				*name;
	t_shape_type		type;
	t_vec3				position;
	t_vec3				target;
	t_vec3				rotation;
	double				scale;
	t_rgba				color;
	double				radius;
	double				angle;
	int					material_id;
	struct s_material	*material;
	double				opacity;
	double				reflection;
	double				refraction;
	double				shine;
	t_bounds			bounds;
	struct s_mesh		*mesh;
	struct s_octree		*octree;
}						t_shape;

int						intersects_shape(struct s_ray *ray, t_shape *shape,
							struct s_raycast_hit *hit, int debug);
int						intersects_sphere(struct s_ray *ray, t_shape *sphere,
							struct s_raycast_hit *hit);
int						intersects_plane(struct s_ray *ray, t_shape *plane,
							struct s_raycast_hit *hit);
int						intersects_cone(struct s_ray *ray, t_shape *cone,
							struct s_raycast_hit *hit);
int						intersects_cylinder(struct s_ray *ray, t_shape *cyl,
							struct s_raycast_hit *hit);
int						intersects_triangle(struct s_ray *ray,
							t_triface *triface, struct s_raycast_hit *hit);
int						intersects_model(struct s_ray *ray, t_shape *model,
							struct s_raycast_hit *hit);
int						intersects_octree_model(struct s_ray *ray,
							t_shape *model, t_octree *node,
							struct s_raycast_hit *hit);

t_vec3					calc_hit_normal(struct s_raycast_hit *hit);
t_vec3					calc_hit_normal_sphere(t_shape *sphere,
							struct s_raycast_hit *hit);
t_vec3					calc_hit_normal_plane(t_shape *plane,
							struct s_raycast_hit *hit);
t_vec3					calc_hit_normal_cone(t_shape *cone,
							struct s_raycast_hit *hit);
t_vec3					calc_hit_normal_cylinder(t_shape *c,
							struct s_raycast_hit *hit);

t_vec2					calc_hit_uv(struct s_raycast_hit *hit);
t_vec2					calc_hit_uv_sphere(t_shape *sphere,
							struct s_raycast_hit *hit);
t_vec2					calc_hit_uv_plane(t_shape *plane,
							struct s_raycast_hit *hit);
t_vec2					calc_hit_uv_cone(t_shape *cone,
							struct s_raycast_hit *hit);
t_vec2					calc_hit_uv_cylinder(t_shape *c,
							struct s_raycast_hit *hit);
t_vec2					calc_hit_uv_triangle(t_shape *model,
							struct s_raycast_hit *hit);

t_vec3					point_on_ray(struct s_ray *r, double t);
int						check_t_hits(struct s_ray *ray,
							struct s_raycast_hit *hit, t_shape *shape);
int						solve_quadratic(t_quadratic q, double *t1, double *t2);

#endif
