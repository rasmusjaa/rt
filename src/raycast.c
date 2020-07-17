/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:10:39 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/17 19:45:24 by rjaakonm         ###   ########.fr       */
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
		intensity = light.intensity * ((double)1 / (distance * distance));
	if (scene->help_ray == 1)
		ft_printf("ray surface dot %f intensity %f, distance %f\n", d, intensity, distance); //
	d = d * intensity;
	return (ft_clamp_d(d, 0, 1));
}

double	ft_pow_d(double n, unsigned int p)
{
	double res;

	res = 1;
	while (p--)
		res *= n;
	return (res);
}

static t_rgba		calc_specular(t_scene *scene, t_raycast_hit hit, t_camera cam)
{
	size_t		i;
	int		falloff; // (0-256)
	t_rgba	total_color;
	t_rgba	color;
	t_vec3	v[2];

	i = 0;
	total_color = ft_make_rgba(0, 0, 0, 1);
	while (i < scene->num_lights)
	{
		v[0] = ft_sub_vec3(scene->lights[i].position, hit.point);
		v[0] = ft_normalize_vec3(ft_reflect_vec3(v[0], hit.normal));
		v[1] = ft_normalize_vec3(ft_sub_vec3(hit.point, cam.position));
		double dot = ft_dot_vec3(v[0], v[1]);
		if (dot > 0)
		{
			falloff = (7 - scene->lights[i].radius) * 10;
			color = scene->lights[i].color;
			double pow = ft_pow_d(dot, falloff);
			color = ft_mul_rgba(color, hit.shape->shine * pow);
			total_color = ft_add_rgba(total_color, color);
		}
		i++;
	}
	return (total_color);
}

double	calc_shadow(t_light light, t_raycast_hit hit, t_scene *scene);

static t_rgba	color_from_lights(t_scene *scene, t_raycast_hit *hit)
{
	size_t		i;
	t_rgba		light;
	t_rgba		total_light;
	double		s;

	i = 0;
	total_light = ft_make_rgba(0, 0, 0, 1);
	while ( i < scene->num_lights)
	{
		s = 0;
		light = scene->lights[i].color;
		if (scene->scene_config.shadows)
			s = calc_shadow(scene->lights[i], *hit, scene);
		if (s < 1 && scene->scene_config.shading)
			light = ft_mul_rgba(light, calc_diffuse(scene->lights[i], *hit, scene));
		light = ft_mul_rgba(light, 1.0 - s);
		total_light = ft_add_rgba(total_light, light);
		i++;
	}
	return (ft_clamp_rgba(total_light));
}

static t_rgba	color_from_shape(t_rgba color, t_scene *scene, t_raycast_hit *hit)
{
	t_rgba		rec;
	t_rgba		rac;
	
	color = ft_mul_rgba_rgba(color, hit->shape->color); // ilman tata mustavalkoseks
	if (scene->scene_config.refraction && hit->shape->refraction > EPSILON)
	{
		rac = calc_refract(scene, hit->ray.direction, *hit, 1.33, hit->depth);
		color = ft_lerp_rgba(color, rac, hit->shape->refraction);
	}
	if (scene->scene_config.reflection && hit->shape->reflection > EPSILON)
	{
		rec = calc_reflect(scene, hit->point, hit->ray.direction, hit->normal, hit->depth);
		color = ft_lerp_rgba(color, rec, hit->shape->reflection);
	}
	return (ft_clamp_rgba(color));
}

static t_rgba	shade(t_scene *scene, t_raycast_hit *hit)
{
	t_rgba		ambient;
	t_rgba		color;
	
	ambient = scene->scene_config.ambient;
	if (!hit->shape)
		return (ambient);
	color = color_from_lights(scene, hit);
	color = color_from_shape(color, scene, hit);
	if (scene->scene_config.specular && hit->shape->shine > EPSILON)
		color = ft_add_rgba(color, calc_specular(scene, *hit, scene->cameras[scene->cur_camera]));
	color = ft_add_rgba(color, ambient);
	return (ft_clamp_rgba(color));
}

typedef struct		s_color_info
{
	double			diffuse;
	double			shadow;
	t_rgba			specular;
	t_rgba			reflect;
	t_rgba			refract;
	t_rgba			color; // final color
}					t_color_info;

// static t_rgba shade(t_scene *scene, t_raycast_hit *hit)
// {
// 	t_rgba ambient;
// 	t_color_info out;
// 	size_t i;

// 	out.shadow = 0;
// 	out.diffuse = 0;
// 	i = 0;
// 	ambient = scene->scene_config.ambient;
// 	if (!hit->shape) // refraction ongelma?
// 		return (ambient);
// 	while (i < scene->num_lights)
// 	{
// 		out.shadow += calc_shadow(scene->lights[i], *hit, scene);
// 		out.diffuse += calc_diffuse(scene->lights[i], *hit, scene);
// 		i++;
// 	}
// 	out.reflect = calc_reflect(scene, hit->point, hit->ray.direction, hit->normal, hit->depth);
// 	out.refract = calc_refract(scene, hit->ray.direction, *hit, 1.33, hit->depth);
// 	out.color = ft_mul_rgba(ft_mul_rgba(hit->shape->color, out.diffuse), 1.0 - out.shadow);
// 	return (ft_lerp_rgba(out.color, out.reflect, hit->shape->reflection));
// }

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
