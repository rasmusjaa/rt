/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:10:39 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 14:11:51 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ft_printf.h"
#include "shape.h"
#include "vector.h"
#include "libft.h"
#include <math.h>
#include "debug.h"
#include "texture.h"
#include "mlx_image.h"
#include "scene.h"

int trace(t_ray *ray, t_scene *scene, t_raycast_hit *hit)
{
	t_raycast_hit cur_hit;
	double	min_dist;
	size_t	i;
	int		hit_found;

	min_dist = INFINITY;
	cur_hit.distance = INFINITY;
	hit_found = FALSE;
	i = 0;
	while (i < scene->num_shapes)
	{
		if (intersects_shape(ray, &scene->shapes[i], &cur_hit, scene->help_ray))
		{
			if (ray->is_shadow)
			{
				if (cur_hit.distance < hit->light_dist && cur_hit.shape != ray->source_shape)
				{
					ray->shadow += cur_hit.shape->material->opacity * (1 - ray->shadow); //material
					hit_found = TRUE;
				}
			}
			else
			{
				if (cur_hit.distance < min_dist)
				{
					hit_found = TRUE;
					*hit = cur_hit;
					min_dist = cur_hit.distance;
					// if (scene->help_ray == 1)
					// 	ft_printf("closest distance %f\n", min_dist);
				}
			}
		}
		i++;
	}
	return (hit_found);
}

t_rgba raycast(t_ray *ray, t_scene *scene, int depth)
{
	t_rgba color;
	t_raycast_hit hit;

	if (scene->cube_map)
		color = sample_cube_map(scene->cube_map->img_data, ray->direction);
	else
		color = scene->scene_config.ambient;
	if (depth > scene->scene_config.bounces)
		return (colorize(scene->scene_config.colorize, ray->last_color));
	hit.shape = NULL;
	ray->scene = scene;
	ray->bump_ray = 0;
	hit.t = INFINITY;
	if (trace(ray, scene, &hit))
	{
		hit.depth = depth;
		hit.normal = calc_hit_normal(&hit);
		hit.uv = calc_hit_uv(&hit);
		if (scene->help_ray)
			ft_printf("uv: %f %f\n", hit.uv.x, hit.uv.y);
		// if (hit.shape->material->texture)
		// {
		//	t_texture *tex = get_texture_by_id(scene, 2);
		//	t_rgba rgb = sample_texture(tex, hit.uv);
		//	double d = hit.shape->refraction;
		//	hit.normal = ft_rotate_vec3(hit.normal, ft_make_vec3(d * (0.5 - rgb.r), d * (0.5 - rgb.g), d * (0.5 - rgb.b)));
		// }
		hit.ray = *ray;
		color = shade(scene, &hit);
	}
	//fogtest
	// double d = ft_clamp_d(hit.t / 100.0, 0, 1);
	// color = ft_add_rgba(ft_mul_rgba(scene->scene_config.ambient, d), ft_mul_rgba(color, 1 - d));
	return (colorize(scene->scene_config.colorize, color));
}
