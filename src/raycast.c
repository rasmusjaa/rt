/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:10:39 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/15 15:09:51 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "vector.h"
#include "libft.h"
#include <math.h>

int	trace(t_ray *ray, t_scene *scene, t_raycast_hit *hit, int stop_at_first)
{
	t_raycast_hit	cur_hit;
	double	min_dist;
	size_t		i;
	int		hit_found;

	min_dist = INFINITY;
	hit_found = FALSE;
	i = 0;
	while (i < scene->num_shapes)
	{
		if (intersects_shape(ray, &scene->shapes[i], &cur_hit))
		{
			if (stop_at_first)
				return (TRUE);
			hit_found = TRUE;
			if (cur_hit.distance < min_dist)
			{
				*hit = cur_hit;
				min_dist = cur_hit.distance;
			}
		}
		i++;
	}
	return (hit_found);
}

// static void		init_color_data(t_color_data *color, t_scene *scene,
// 									t_hit *hit)
// {
// 	color->ambient = ft_mul_rgba(hit->object->color,
// 		ft_intensity_rgba(scene->ambient_color));
// 	color->diffuse = ft_make_rgba(0, 0, 0, 1);
// 	color->specular = ft_make_rgba(0, 0, 0, 1);
// 	color->attenuation = 0.0;
// }

// static t_rgba	calc_reflect(t_scene *scene, t_vec3 point, t_vec3 idir, t_vec3 normal, int depth)
// {
// 	t_ray			reflect_ray;
// 	t_raycasthit	reflect_hit;
// 	t_rgba			color;

// 	reflect_ray.origin = ft_add_vec3(point, ft_mul_vec3(normal, REFLECT_BIAS));
// 	reflect_ray.direction = ft_normalize_vec3(ft_reflect_vec3(idir, normal));
// 	color = raycast(&reflect_ray, scene, &reflect_hit, depth + 1);
// 	//hit->color = ft_lerp_rgba(hit->color, reflect_hit.color, hit->object->reflect);
// 	return (color);
// }

static t_rgba	shade(t_scene *scene, t_raycast_hit *hit)
{
	scene = 0;
	return (hit->shape->color);
}

t_rgba			raycast(t_ray *ray, t_scene *scene)
{
	t_rgba color;
	t_raycast_hit hit;

	color = ft_make_rgba(0.2, 0.2, 0.2, 1.0);
	if (trace(ray, scene, &hit, FALSE))
		color = shade(scene, &hit);
	return (ft_clamp_rgba(color));
}
