/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:10:39 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/17 18:34:26 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "shape.h"
#include "vector.h"
#include "libft.h"
#include <math.h>

int trace(t_ray *ray, t_scene *scene, t_raycast_hit *hit, int stop_at_first)
{
	t_raycast_hit cur_hit;
	double min_dist;
	size_t i;
	int hit_found;

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

// static double calc_fresnel(double amt, double n1, double n2, t_vec3 normal, t_vec3 idir)
// {
// 	double r0 = (n1 - n2) / (n1 + n2);
// 	r0 *= r0;
// 	double cosX = -ft_dot_vec3(normal, idir);
// 	if (n1 > n2)
// 	{
// 		double n = n1 / n2;
// 		double sinT2 = n * n * (1.0 - cosX * cosX);
// 		if (sinT2 > 1.0)
// 			return (1.0);
// 		cosX = sqrt(1.0 - sinT2);
// 	}
// 	double x = 1.0 - cosX;
// 	double ret = r0 + (1.0 - r0) * x * x * x * x * x;

// 	ret = (amt + (1.0 - amt) * ret);
// 	return (ret);
// }

double ft_clamp_range(double v, double min, double max)
{
	if (v < min)
		return (min);
	else if (v > max)
		return (max);
	return(v);
}

// void fresnel(const Vec3f &I, const Vec3f &N, const float &ior, float &kr)
static double calc_fresnel(t_vec3 normal, t_vec3 idir, double ior)
{
	double kr;
	double cosi = ft_clamp_range(ft_dot_vec3(idir, normal), -1, 1);
	double etai = 1, etat = ior;
	if (cosi > 0)
	{
		ft_swap_d(&etai, &etat);
	}
	// Compute sini using Snell's law
	double sint = etai / etat * sqrtf(ft_max_d(0.f, 1 - cosi * cosi));
	// Total internal reflection
	if (sint >= 1)
	{
		kr = 1;
	}
	else
	{
		double cost = sqrtf(ft_max_d(0.f, 1 - sint * sint));
		cosi = fabs(cosi);
		double Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		double Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		kr = (Rs * Rs + Rp * Rp) / 2;
	}
	// As a consequence of the conservation of energy, transmittance is given by:
	// kt = 1 - kr;
	return (kr);
}

static t_rgba calc_reflect(t_scene *scene, t_raycast_hit hit, t_vec3 idir, t_vec3 normal, int depth)
{
	t_ray reflect_ray;
	t_rgba color;

	reflect_ray.origin = ft_add_vec3(hit.point, ft_mul_vec3(normal, EPSILON));
	reflect_ray.direction = ft_normalize_vec3(ft_reflect_vec3(idir, normal));
	color = raycast(&reflect_ray, scene, depth + 1);
	if (scene->help_ray == 1)
		print_rgba("reflect color", color);
	return (color);
}

t_vec3 ft_refract_vec3(t_vec3 i, t_vec3 normal, double ior)
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
	return k < 0 ? ft_make_vec3(0, 0, 0) : ft_add_vec3(ft_mul_vec3(i, eta), ft_mul_vec3(n, (eta * cosi - sqrtf(k))));
}

static t_rgba calc_refract(t_scene *scene, t_vec3 idir, t_raycast_hit hit, double ior, int depth)
{
	t_ray refract_ray;
	t_rgba color;

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

static double calc_diffuse(t_light light, t_raycast_hit hit, t_scene *scene)
{
	double d;
	double distance;
	double intensity;
	t_vec3 light_dir;

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

double calc_shadow(t_light light, t_raycast_hit hit, t_scene *scene);

typedef struct s_color_info
{
	double diffuse;
	double shadow;
	double fresnel;
	t_rgba specular;
	t_rgba reflect;
	t_rgba refract;
	t_rgba color; // final color
} t_color_info;

static t_rgba shade(t_scene *scene, t_raycast_hit *hit)
{
	t_rgba ambient;
	t_color_info out;
	size_t i;

	out.shadow = 0;
	out.diffuse = 0;
	out.fresnel = 0;

	i = 0;
	ambient = scene->scene_config.ambient;
	if (!hit->shape) // refraction ongelma?
		return (ambient);
	while (i < scene->num_lights)
	{
		out.shadow += calc_shadow(scene->lights[i], *hit, scene);
		out.diffuse += calc_diffuse(scene->lights[i], *hit, scene) / (double)scene->num_lights;
		i++;
	}

	out.color = ft_mul_rgba(hit->shape->color, out.diffuse);
	// out.refract = calc_refract(scene, hit->ray.direction, *hit, 1.33, hit->depth);

	if (hit->shape->refraction > 0)
	{
		out.refract = calc_refract(scene, hit->ray.direction, *hit, 1.5, hit->depth);

		out.color = ft_lerp_rgba(out.color, out.refract, hit->shape->refraction);
	}

	if (hit->shape->reflection > 0)
	{
		out.reflect = calc_reflect(scene, *hit, hit->ray.direction, hit->normal, hit->depth);
		// out.fresnel = calc_fresnel(hit->shape->reflection, 1.0, 5.33, hit->normal, hit->ray.direction);
		out.fresnel = calc_fresnel(hit->normal, hit->ray.direction, 1.33);
		out.color = ft_lerp_rgba(out.color, out.reflect, out.fresnel);
	}
	return (out.color);
}
static void init_hit_info(t_raycast_hit *hit)
{
	hit->shape = NULL;
}

t_rgba raycast(t_ray *ray, t_scene *scene, int depth)
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
