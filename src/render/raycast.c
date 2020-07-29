/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:10:39 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/28 18:41:39 by sluhtala         ###   ########.fr       */
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

	reflect_ray.origin = hit.point;// ft_add_vec3(hit.point, ft_mul_vec3(normal, EPSILON));
	reflect_ray.direction = ft_normalize_vec3(ft_reflect_vec3(idir, normal));
	reflect_ray.is_shadow = FALSE;
	reflect_ray.last_color = hit.shape->material->diffuse; //shape->color to shape->material->diffuse
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

	refract_ray.origin = hit.point;// ft_add_vec3(hit.point, ft_mul_vec3(ft_invert_vec3(hit.normal), EPSILON));
	refract_ray.direction = ft_refract_vec3(idir, hit.normal, ior);
	refract_ray.direction = ft_normalize_vec3(refract_ray.direction);
	refract_ray.is_shadow = FALSE;
	refract_ray.last_color = hit.shape->material->diffuse; //shape->color to shape->material->diffuse
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
	d = ft_clamp_d(ft_dot_vec3(light_dir, hit.normal), 0, 1) + (1.0 - hit.shape->material->opacity); //material->opacity
	if (light.type == DIRECTIONAL)
		intensity = light.intensity / 1000;
	else
		intensity = light.intensity * ((double)1 / (distance * distance));
	if (scene->help_ray == 1)
	{
		print_vec3("shape normal", hit.normal);
		print_vec3("light dir", light_dir);
		ft_printf("ray surface dot %f intensity %f, distance %f\n", d, intensity, distance); //
	}
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
			color = ft_mul_rgba(color, hit.shape->material->shininess * pow); //material->shininess
			total_color = ft_add_rgba(total_color, color);
		}
		i++;
	}
	return (total_color);
}

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
	double		refraction;
	double		fresnel;
	int			rec_calced;

//	color = ft_mul_rgba_rgba(color, hit->shape->material->diffuse); //shape->color to material->diffuse /ilman tata mustavalkoseks
	color = ft_mul_rgba_rgba(color, ft_add_rgba(hit->shape->material->diffuse, sample_texture(hit->shape->material->texture, hit->uv)));
	rec_calced = FALSE;
	if (scene->scene_config.opacity && hit->shape->material->opacity < 1 - EPSILON) //material->opacity
	{
		refraction = scene->scene_config.refraction ? hit->shape->material->refra_index : 1; //material->refra_index
		rac = calc_refract(scene, hit->ray.direction, *hit, refraction, hit->depth);
		if (scene->scene_config.refraction && refraction > 1 + EPSILON)
		{
			fresnel = calc_fresnel(hit->normal, hit->ray.direction, refraction);
			rec = calc_reflect(scene, *hit, hit->ray.direction, hit->normal, hit->depth);
			rec_calced = TRUE;
			rac = ft_lerp_rgba(rac, rec, fresnel);
		}
		color = ft_lerp_rgba(color, rac, 1 - hit->shape->material->opacity); //opacity to material->opacity
	}
	if (scene->scene_config.reflection && hit->shape->material->reflection > EPSILON) //material
	{
		if (!rec_calced)
			rec = calc_reflect(scene, *hit, hit->ray.direction, hit->normal, hit->depth);
		color = ft_lerp_rgba(color, rec, hit->shape->material->reflection); //material
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
	color = ft_add_rgba(color, scene->scene_config.ambient);
	color = color_from_shape(color, scene, hit);
	if (scene->scene_config.specular && hit->shape->material->shininess > EPSILON) //material->shininess
		color = ft_add_rgba(color, calc_specular(scene, *hit, scene->cameras[scene->cur_camera]));
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

t_rgba	colorize(size_t colorize, t_rgba color)
{
	double	c;
	t_rgba	copy;

	copy.r = color.r;
	copy.g = color.g;
	copy.b = color.b;
	copy.a = color.a;

	if (colorize)
	{
		c = ft_intensity_rgba(color);
		if (colorize == 1)
			color = ft_make_rgba(c, c, c, color.a);
		else if (colorize == 2)
			color = ft_sub_rgba(ft_make_rgba(1, 1, 1, 1), color);
		else if (colorize == 3)
		{
			color.r = (copy.r * .393) + (copy.g *.769) + (copy.b * .189);
			color.g = (copy.r * .349) + (copy.g *.686) + (copy.b * .168);
			color.b = (copy.r * .272) + (copy.g *.534) + (copy.b * .131);
		}
		else if (colorize == 4)
			color = ft_make_rgba(c, 0, 0, color.a);
		else if (colorize == 5)
			color = ft_make_rgba(0, c, 0, color.a);
		else if (colorize == 6)
			color = ft_make_rgba(0, 0, c, color.a);

	}
	return (ft_clamp_rgba(color));
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
	return (colorize(scene->scene_config.colorize, color));
}
