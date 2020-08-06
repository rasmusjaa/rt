/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:30:07 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/06 15:33:53 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "color.h"
#include "scene.h"
#include "shape.h"
#include "libft.h"
#include "debug.h"
#include "ft_printf.h"

t_rgba	calc_specular(t_scene *scene, t_raycast_hit hit, t_camera cam)
{
	size_t	i;
	t_rgba	total_color;
	t_rgba	color;
	t_vec3	v[2];
	double	dot;

	i = 0;
	total_color = ft_make_rgba(0, 0, 0, 1);
	while (i < scene->num_lights)
	{
		v[0] = ft_sub_vec3(scene->lights[i].position, hit.point);
		v[0] = ft_normalize_vec3(ft_reflect_vec3(v[0], hit.normal));
		v[1] = ft_normalize_vec3(ft_sub_vec3(hit.point, cam.position));
		dot = ft_dot_vec3(v[0], v[1]);
		if (dot > 0)
		{
			color = scene->lights[i].color;
			color = ft_mul_rgba(color, hit.shape->material->shininess *
				ft_pow_d(dot, (7 - scene->lights[i].radius) * 10));
			total_color = ft_add_rgba(total_color, color);
		}
		i++;
	}
	return (total_color);
}

double	calc_diffuse(t_light light, t_raycast_hit hit)
{
	double d;
	double distance;
	double intensity;
	t_vec3 light_dir;

	if (light.type == DIRECTIONAL)
		light_dir = ft_sub_vec3(light.position, hit.point);
	else
		light_dir = ft_sub_vec3(light.position, hit.point);
	distance = ft_len_vec3(light_dir);
	light_dir = ft_normalize_vec3(light_dir);
	d = ft_dot_vec3(light_dir, hit.normal);
	if (hit.shape->type == PLANE || hit.shape->type == MODEL)
		d = ft_abs_d(d);
	d = ft_clamp_d(d, 0, 1) +
		(1.0 - hit.shape->material->opacity);
	if (light.type == DIRECTIONAL)
		intensity = light.intensity / 1000;
	else
		intensity = light.intensity * (1.0 / (distance * distance));
	d = d * intensity;
	return (ft_clamp_d(d, 0, 1));
}

double	calc_fresnel(t_vec3 normal, t_vec3 idir, double ior)
{
	t_fresnel_params params;

	params.etai = 1;
	params.etat = ior;
	params.cosi = ft_clamp_range(ft_dot_vec3(idir, normal), -1, 1);
	if (params.cosi > 0)
		ft_swap_d(&params.etai, &params.etat);
	params.sint = params.etai / params.etat *
		sqrtf(ft_max_d(0.f, 1 - params.cosi * params.cosi));
	if (params.sint >= 1)
		params.kr = 1;
	else
	{
		params.cost = sqrtf(ft_max_d(0.f, 1 - params.sint * params.sint));
		params.cosi = fabs(params.cosi);
		params.rs = ((params.etat * params.cosi) - (params.etai * params.cost))
			/ ((params.etat * params.cosi) + (params.etai * params.cost));
		params.rp = ((params.etai * params.cosi) - (params.etat * params.cost))
			/ ((params.etai * params.cosi) + (params.etat * params.cost));
		params.kr = (params.rs * params.rs + params.rp * params.rp) / 2;
	}
	return (params.kr);
}
