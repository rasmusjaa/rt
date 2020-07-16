/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:10:39 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/16 18:22:55 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "shape.h"
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
	cur_hit.distance = INFINITY;
	hit_found = FALSE;
	i = 0;
	while (i < scene->num_shapes)
	{
		if (intersects_shape(ray, &scene->shapes[i], &cur_hit, scene->help_ray))
		{
			if (stop_at_first)
			{
				if (cur_hit.distance < hit->light_dist)
					return TRUE;
			}
			else // to not accept shadow if shadow is behind light
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

// static void		init_color_data(t_color_data *color, t_scene *scene,
// 									t_hit *hit)
// {
// 	color->ambient = ft_mul_rgba(hit->object->color,
// 		ft_intensity_rgba(scene->ambient_color));
// 	color->diffuse = ft_make_rgba(0, 0, 0, 1);
// 	color->specular = ft_make_rgba(0, 0, 0, 1);
// 	color->attenuation = 0.0;
// }

static t_rgba	calc_reflect(t_scene *scene, t_vec3 point, t_vec3 idir, t_vec3 normal, int depth)
{
	t_ray			reflect_ray;
	t_rgba			color;

	reflect_ray.origin = ft_add_vec3(point, ft_mul_vec3(normal, EPSILON));
	reflect_ray.direction = ft_normalize_vec3(ft_reflect_vec3(idir, normal));
	color = raycast(&reflect_ray, scene, depth + 1);
	if (scene->help_ray == 1)
		print_rgba("reflect color", color);
	return (color);
}

t_vec3			ft_refract_vec3(t_vec3 i, t_vec3 normal, double ior)
{
	double cosi = ft_clamp_d(ft_dot_vec3(i, normal), -1, 1);
	double etai = 1, etat = ior;
	t_vec3 n = normal;
	if (cosi < 0)
	{
		cosi = -cosi;
	}
	else
	{
		ft_swap_d(&etai, &etat);
		n = ft_invert_vec3(normal);
	}
	double eta = etai / etat;
	double k = 1 - eta * eta * (1 - cosi * cosi);
	return k < 0 ? ft_make_vec3(0,0,0) : ft_add_vec3(ft_mul_vec3(i, eta), ft_mul_vec3(n, (eta * cosi - sqrtf(k))));
}

static t_rgba	calc_refract(t_scene *scene, t_vec3 idir, t_raycast_hit hit, double ior, int depth)
{
	t_ray			refract_ray;
	t_rgba			color;

	refract_ray.origin = hit.point; // ft_add_vec3(hit.point, ft_mul_vec3(ft_invert_vec3(hit.normal), EPSILON));
	refract_ray.direction = ft_refract_vec3(idir, hit.normal, ior);
	refract_ray.direction = ft_normalize_vec3(refract_ray.direction);
	color = raycast(&refract_ray, scene, depth + 1);
	if (scene->help_ray == 1)
	{
		print_rgba("refract color", color);
		print_vec3("rdir: ", refract_ray.direction);
	}
	return (color);
}

static double		calc_diffuse(t_light light, t_raycast_hit hit, t_scene *scene)
{
	double	d;
	double	distance;
	double	intensity;
	t_vec3	light_dir;

	if (light.type == DIRECTIONAL)
		light_dir = ft_sub_vec3(light.position, hit.point); // light needs a target field or rotation that we can calculate a direction from
	else
		light_dir = ft_sub_vec3(light.position, hit.point);
	distance = ft_len_vec3(light_dir);
	light_dir = ft_normalize_vec3(light_dir);
	d = ft_dot_vec3(light_dir, hit.normal);
	if (light.type == DIRECTIONAL)
		intensity = light.intensity / 1000;
	else
		intensity = light.intensity / (40 * M_PI * distance);
	d = d * intensity;
	if (scene->help_ray == 1)
		ft_printf(" ray surface dot %f\n", d); //
	return (ft_clamp_d(d, 0, 1));

}

double	calc_shadow(t_light light, t_raycast_hit hit, t_scene *scene);

static t_rgba	shade(t_scene *scene, t_raycast_hit *hit)
{
	t_rgba		ambient;
	t_rgba		total_light;
	t_rgba		light;
	t_rgba		object_c;
	t_rgba		rec;
	t_rgba		rac;
	double		reflect;
	double		refract;
	size_t		i;
	double		d;
	double		s;

	s = 0;

	i = 0;
	d = 0;
	total_light = ft_make_rgba(0, 0, 0, 1);
	ambient = scene->scene_config.ambient;
	if (!hit->shape) // refraction ongelma?
		return (ambient);
	object_c = hit->shape->color;
	reflect = scene->scene_config.reflection == 1 ? hit->shape->reflection : 0;
	refract = scene->scene_config.refraction == 1 ? hit->shape->refraction : 0;
	if (hit->shape)
	{
		while ( i < scene->num_lights)
		{
			if (scene->scene_config.shadows == 0)
				light = ft_make_rgba(1, 1, 1, 1);
			else
			{
				light = scene->lights[i].color;
				if (scene->lights[i].radius >= 1)
					s = calc_shadow(scene->lights[i], *hit, scene);
				else if (in_shadow(scene->lights[i], *hit, scene))
					light = ft_make_rgba(0, 0, 0, 1);
			}
			d = scene->scene_config.shading == 1 ? calc_diffuse(scene->lights[i], *hit, scene) : 1;
			light = ft_mul_rgba(light, d);
			total_light = ft_add_rgba(total_light, light);
			total_light = ft_mul_rgba(total_light, 1.0 - s);
			// if (scene->help_ray)
			// 	ft_printf("shadow softness: %f\n", s);
			i++;
		}
		total_light = ft_mul_rgba_rgba(total_light, object_c); // ilman tata mustavalkoseks
		total_light = ft_add_rgba(total_light, ambient);
		rec = calc_reflect(scene, hit->point, hit->ray.direction, hit->normal, hit->depth);
		if (scene->scene_config.refraction > EPSILON)
		{
			rac = calc_refract(scene, hit->ray.direction, *hit, 1.33, hit->depth);
			total_light = ft_lerp_rgba(total_light, rac, refract);
		}
		total_light = ft_lerp_rgba(total_light, rec, reflect);
		// if (scene->help_ray)
		// 	print_rgba("color", total_light);
		return (total_light);
	}
	return (ambient);
}

static void		init_hit_info(t_raycast_hit *hit)
{
	hit->shape = NULL;
}

t_rgba			raycast(t_ray *ray, t_scene *scene, int depth)
{
	t_rgba color;
	t_raycast_hit hit;

	color = scene->scene_config.ambient;
	if (depth > scene->scene_config.bounces)
		return (color);
	init_hit_info(&hit);
	if (trace(ray, scene, &hit, FALSE))
	{
		hit.depth = depth;
		hit.normal = calc_hit_normal(&hit);
		hit.ray = *ray;
		color = shade(scene, &hit);
	}
	return (ft_clamp_rgba(color));
}
