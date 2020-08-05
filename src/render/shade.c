/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:26:30 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 14:57:37 by wkorande         ###   ########.fr       */
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
		rac = calc_refract(scene, hit->ray.direction, *hit, refraction);
		if (scene->scene_config.refraction && refraction > 1 + EPSILON)
		{
			fresnel = calc_fresnel(hit->normal, hit->ray.direction, refraction);
			rec = calc_reflect(scene, *hit, hit->ray.direction, hit->normal);
			rec_calced = TRUE;
			rac = ft_lerp_rgba(rac, rec, fresnel);
		}
		color = ft_lerp_rgba(color, rac, 1 - hit->shape->material->opacity); //opacity to material->opacity
	}
	if (scene->scene_config.reflection && hit->shape->material->reflection > EPSILON) //material
	{
		if (!rec_calced)
			rec = calc_reflect(scene, *hit, hit->ray.direction, hit->normal);
		color = ft_lerp_rgba(color, rec, hit->shape->material->reflection); //material
	}
	return (ft_clamp_rgba(color));
}

t_rgba	shade(t_scene *scene, t_raycast_hit *hit)
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
