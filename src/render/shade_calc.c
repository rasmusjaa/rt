/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:30:07 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 14:14:17 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "color.h"
#include "scene.h"
#include "shape.h"
#include "libft.h"
#include "debug.h"
#include "ft_printf.h"

t_rgba		calc_specular(t_scene *scene, t_raycast_hit hit, t_camera cam)
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

double calc_diffuse(t_light light, t_raycast_hit hit, t_scene *scene)
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
		ft_printf("ray surface dot %f intensity %f, distance %f\n", d, intensity, hit.distance); //
	}
	d = d * intensity;
	return (ft_clamp_d(d, 0, 1));
}

double calc_fresnel(t_vec3 normal, t_vec3 idir, double ior)
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
