/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_calc_reflect_refract.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:38:33 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 14:17:27 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "shape.h"
#include "scene.h"
#include "debug.h"

t_rgba	calc_reflect(t_scene *scene, t_raycast_hit hit, t_vec3 idir, t_vec3 normal, int depth)
{
	t_ray	reflect_ray;
	t_rgba	color;

	reflect_ray.origin = hit.point;
	reflect_ray.direction = ft_normalize_vec3(ft_reflect_vec3(idir, normal));
	reflect_ray.is_shadow = FALSE;
	reflect_ray.last_color = hit.shape->material->diffuse;
	color = raycast(&reflect_ray, scene, depth + 1);
	if (scene->help_ray == 1)
		print_rgba("reflect color", color);
	return (color);
}

t_rgba	calc_refract(t_scene *scene, t_vec3 idir, t_raycast_hit hit, double ior, int depth)
{
	t_ray	refract_ray;
	t_rgba	color;

	refract_ray.origin = hit.point;
	refract_ray.direction = ft_refract_vec3(idir, hit.normal, ior);
	refract_ray.direction = ft_normalize_vec3(refract_ray.direction);
	refract_ray.is_shadow = FALSE;
	refract_ray.last_color = hit.shape->material->diffuse;
	color = raycast(&refract_ray, scene, depth + 1);
	if (scene->help_ray == 1)
	{
		print_rgba("refract color", color);
		print_vec3("rdir: ", refract_ray.direction);
	}
	return (color);
}
