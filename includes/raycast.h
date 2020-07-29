/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:24:35 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/29 14:06:48 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "rt.h"
# include "vector.h"
# include "color.h"
# include "object.h"

struct s_shape;
struct s_scene;
struct s_light;
struct s_triface;

typedef struct		s_ray
{
	t_vec3			origin;
	t_vec3			direction;
	struct s_shape	*source_shape;
	double			shadow;
	int				is_shadow;
	t_rgba			last_color;
	double			last_opacity;
	struct s_scene	*scene;
	size_t			bump_ray;
	t_vec2			uv;
}					t_ray;

typedef struct		s_raycast_hit
{
	t_vec3			point;
	t_vec3			normal;
	struct s_shape	*shape;
	t_vec3			light_dir;
	double			t;
	double			t2;
	double			distance;
	double			light_dist;
	t_rgba			color;
	int				depth;
	t_vec3			idir;
	t_ray			ray;
	struct s_triface *triface;
	t_vec2			uv;
}					t_raycast_hit;

t_rgba				raycast(t_ray *ray, struct s_scene *scene, int depth);
int					trace(t_ray *ray, struct s_scene *scene, t_raycast_hit *hit);
double				in_shadow(struct s_light light, t_raycast_hit hit,
						struct s_scene *scene);
double				calc_shadow(struct s_light light, t_raycast_hit hit,
						struct s_scene *scene);

#endif
