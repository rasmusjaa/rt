/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:26:30 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/06 14:55:02 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "scene.h"
#include "color.h"
#include "shape.h"
#include "texture.h"

static t_rgba	color_from_lights(t_scene *scene, t_raycast_hit *hit)
{
	size_t		i;
	t_rgba		light;
	t_rgba		total_light;
	double		s;

	i = 0;
	total_light = ft_make_rgba(0, 0, 0, 1);
	while (i < scene->num_lights)
	{
		s = 0;
		light = scene->lights[i].color;
		if (scene->scene_config.shadows)
			s = calc_shadow(scene->lights[i], *hit, scene);
		if (s < 1 && scene->scene_config.shading)
			light = ft_mul_rgba(light, calc_diffuse(scene->lights[i], *hit));
		light = ft_mul_rgba(light, 1.0 - s);
		total_light = ft_add_rgba(total_light, light);
		i++;
	}
	return (ft_clamp_rgba(total_light));
}

static int		set_rec_calced(t_scene *scene, t_raycast_hit *hit,
	t_rgba *rec, t_rgba *rac)
{
	double fresnel;
	double refraction;

	refraction = hit->shape->material->refra_index;
	fresnel = calc_fresnel(hit->normal, hit->ray.direction, refraction);
	*rec = calc_reflect(scene, *hit, hit->ray.direction,
		hit->normal);
	*rac = ft_lerp_rgba(*rac, *rec, fresnel);
	return (TRUE);
}

static t_rgba	color_diffuse_texture(t_raycast_hit *hit, t_rgba color)
{
	return (ft_mul_rgba_rgba(color,
		ft_add_rgba(hit->shape->material->diffuse,
			sample_texture(hit->shape->material->texture, hit->uv))));
}

static t_rgba	color_from_shape(t_rgba color, t_scene *scene,
	t_raycast_hit *hit)
{
	t_rgba		rera[2];
	double		r;
	int			rec_calced;

	color = color_diffuse_texture(hit, color);
	rec_calced = FALSE;
	if (scene->scene_config.opacity && hit->shape->material->opacity <
		1 - EPSILON)
	{
		r = scene->scene_config.refraction ?
			hit->shape->material->refra_index : 1;
		rera[1] = calc_refract(scene, hit->ray.direction, *hit, r);
		if (scene->scene_config.refraction && r > 1 + EPSILON)
			rec_calced = set_rec_calced(scene, hit, &rera[0], &rera[1]);
		color = ft_lerp_rgba(color, rera[1], 1 - hit->shape->material->opacity);
	}
	if (scene->scene_config.reflection &&
		hit->shape->material->reflection > EPSILON)
	{
		if (!rec_calced)
			rera[0] = calc_reflect(scene, *hit, hit->ray.direction,
				hit->normal);
		color = ft_lerp_rgba(color, rera[0], hit->shape->material->reflection);
	}
	return (ft_clamp_rgba(color));
}

t_rgba			shade(t_scene *scene, t_raycast_hit *hit)
{
	t_rgba		ambient;
	t_rgba		color;

	ambient = scene->scene_config.ambient;
	if (!hit->shape)
		return (ambient);
	color = color_from_lights(scene, hit);
	color = ft_add_rgba(color, scene->scene_config.ambient);
	color = color_from_shape(color, scene, hit);
	if (scene->scene_config.specular &&
		hit->shape->material->shininess > EPSILON)
		color = ft_add_rgba(color,
			calc_specular(scene, *hit, scene->cameras[scene->cur_camera]));
	return (ft_clamp_rgba(color));
}
