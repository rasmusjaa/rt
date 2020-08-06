/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:10:39 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/06 15:59:41 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ft_printf.h"
#include "shape.h"
#include "vector.h"
#include "libft.h"
#include "debug.h"
#include "texture.h"
#include "mlx_image.h"
#include "scene.h"

t_vec3		point_on_ray(t_ray *r, double t)
{
	t_vec3 p;

	p = ft_add_vec3(r->origin, ft_mul_vec3(r->direction, t));
	return (p);
}

static int	shadow_check(t_ray *ray, t_raycast_hit *hit,
	t_raycast_hit *cur_hit, double *min_dist)
{
	int hit_found;

	hit_found = FALSE;
	if (ray->is_shadow)
	{
		if (cur_hit->distance < hit->light_dist && cur_hit->shape !=
			ray->source_shape)
		{
			ray->shadow += cur_hit->shape->material->opacity *
				(1 - ray->shadow);
			hit_found = TRUE;
		}
	}
	else
	{
		if (cur_hit->distance < *min_dist)
		{
			hit_found = TRUE;
			*hit = *cur_hit;
			*min_dist = cur_hit->distance;
		}
	}
	return (hit_found);
}

int			trace(t_ray *ray, t_scene *scene, t_raycast_hit *hit)
{
	t_raycast_hit	cur_hit;
	double			min_dist;
	int				hit_found;
	size_t			i;

	min_dist = INFINITY;
	cur_hit.distance = INFINITY;
	hit_found = FALSE;
	i = 0;
	while (i < scene->num_shapes)
	{
		if (intersects_shape(ray, &scene->shapes[i], &cur_hit, scene->help_ray))
		{
			if (shadow_check(ray, hit, &cur_hit, &min_dist))
				hit_found = TRUE;
		}
		i++;
	}
	return (hit_found);
}

t_rgba		raycast(t_ray *ray, t_scene *scene, int depth)
{
	t_rgba			color;
	t_raycast_hit	hit;

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
		if (hit.shape->material->texture)
			hit.uv = calc_hit_uv(&hit);
		if (scene->help_ray)
			ft_printf("uv: %f %f\n", hit.uv.x, hit.uv.y);
		hit.ray = *ray;
		color = shade(scene, &hit);
	}
	return (colorize(scene->scene_config.colorize, color));
}
