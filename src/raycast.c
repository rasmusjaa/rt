/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:10:39 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/11 16:17:51 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "vector.h"
#include "libft.h"
#include <math.h>

int				trace(t_ray *ray, t_scene *scene, t_hit *hit,
						int stop_at_first)
{
	t_hit	cur_hit;
	double	min_dist;
	int		i;
	int		hit_found;

	min_dist = INFINITY;
	hit_found = FALSE;
	i = 0;
	while (i < scene->num_objects)
	{
		if (intersects_object(ray, &scene->objects[i], &cur_hit))
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

static void		init_color_data(t_color_data *color, t_scene *scene,
									t_hit *hit)
{
	color->ambient = ft_mul_rgba(hit->object->color,
		ft_intensity_rgba(scene->ambient_color));
	color->diffuse = ft_make_rgba(0, 0, 0, 1);
	color->specular = ft_make_rgba(0, 0, 0, 1);
	color->attenuation = 0.0;
}

static t_rgba	calc_reflect(t_scene *scene, t_vec3 point, t_vec3 idir, t_vec3 normal, int depth)
{
	t_ray			reflect_ray;
	t_raycasthit	reflect_hit;
	t_rgba			color;

	reflect_ray.origin = ft_add_vec3(point, ft_mul_vec3(normal, REFLECT_BIAS));
	reflect_ray.direction = ft_normalize_vec3(ft_reflect_vec3(idir, normal));
	color = raycast(&reflect_ray, scene, &reflect_hit, depth + 1);
	//hit->color = ft_lerp_rgba(hit->color, reflect_hit.color, hit->object->reflect);
	return (color);
}

static t_rgba	shade(t_scene *scene, t_hit *hit)
{
	t_color_data	color;
	int				i;

	init_color_data(&color, scene, hit);
	i = 0;
	while (i < scene->num_lights)
	{
		color.attenuation = 1.0 - (hit->distance / MAX_DISTANCE);
		if (!is_in_shadow(&scene->lights[i], scene, hit))
		{
			color.diffuse = ft_add_rgba(color.diffuse,
				calc_diffuse(&scene->lights[i], hit));
			color.specular = ft_add_rgba(color.specular,
				calc_specular(&scene->lights[i], hit, scene->camera.pos));
		}
		color.diffuse = ft_mul_rgba(color.diffuse, color.attenuation);
		color.specular = ft_mul_rgba(color.specular, color.attenuation);
        
		i++;
	}
	color.out = ft_add_rgba(color.ambient, ft_add_rgba(
		ft_mul_rgba_rgba(hit->object->color, color.diffuse), color.specular));
	return (color.out);
}

typedef struct	s_hit
{
	t_vec3		point;
	t_vec3		normal;
	t_object	*object;
	t_vec3		light_dir;
	double		t;
	double		t2;
	double		distance;
	t_rgba		color;
}				t_hit;

t_rgba			raycast(t_ray *ray, t_scene *scene)
{
	t_rgba color;
    t_hit 
	color = scene->ambient_color;
	if (trace(ray, scene, hit, FALSE))
		color = shade(scene, hit);
	return (ft_clamp_rgba(color));
}
