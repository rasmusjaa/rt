/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:10:39 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/13 21:19:42 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
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
	hit_found = FALSE;
	i = 0;
	while (i < scene->num_shapes)
	{
		if (intersects_shape(ray, &scene->shapes[i], &cur_hit, scene->help_ray))
		{
			if (stop_at_first == 1) // tarviiks muuhun vai oliks varjoo varten?
				return (TRUE);
			if (stop_at_first != 2 || cur_hit.distance < hit->light_dist) // to not accept shadow if shadow is behind light
			{
				hit_found = TRUE; 
				if (cur_hit.distance < min_dist)
				{
					*hit = cur_hit;
					min_dist = cur_hit.distance;
					if (scene->help_ray == 1)
						ft_printf("closest distance %f\n", min_dist);
				}
			}
		}
		i++;
	}
	// if (!hit_found && intersects_model(ray, &scene->model, &cur_hit, scene->help_ray))
	// {
	// 	hit_found = TRUE;
	// 	hit->shape = NULL;
	// 	*hit = cur_hit;
	// 	if (scene->help_ray == 1)
	// 		ft_printf("closest dist %f\n", hit->distance);
	// }
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

// static t_rgba	calc_reflect(t_scene *scene, t_vec3 point, t_vec3 idir, t_vec3 normal, int depth)
// {
// 	t_ray			reflect_ray;
// 	t_raycasthit	reflect_hit;
// 	t_rgba			color;

// 	reflect_ray.origin = ft_add_vec3(point, ft_mul_vec3(normal, REFLECT_BIAS));
// 	reflect_ray.direction = ft_normalize_vec3(ft_reflect_vec3(idir, normal));
// 	color = raycast(&reflect_ray, scene, &reflect_hit, depth + 1);
// 	//hit->color = ft_lerp_rgba(hit->color, reflect_hit.color, hit->object->reflect);
// 	return (color);
// }

static double		spot_shading(t_light light, t_raycast_hit hit, t_scene *scene)
{
	double	d;
	double	distance;
	double	intensity;
	t_vec3	light_ray;

	light_ray = ft_sub_vec3(light.position, hit.point);
	distance = ft_len_vec3(light_ray);
	light_ray = ft_normalize_vec3(light_ray);
	d = ft_dot_vec3(light_ray, hit.normal);
	if (light.type == 1)
		intensity = light.intensity / 1000;
	else
		intensity = light.intensity / 10 * (1 / (1 + distance + ft_pow(distance, 2)));
	if (scene->help_ray == 1)
		ft_printf("dot %f intensity %d\n", d, intensity); //
//	d *= intensity;
	d = ft_clamp_d(d, 0, 1);
	return (d);
	
}

static int		in_shadow(t_light light, t_raycast_hit hit, t_scene *scene)
{
	t_ray	ray;
	t_raycast_hit new_hit;
	
	ray.origin = hit.point;
	ray.direction = ft_sub_vec3(light.position, hit.point);
	new_hit.light_dist = ft_len_vec3(ray.direction);
	if (scene->help_ray)
		ft_printf("testing shadow of %f %f %f\n", hit.point.x, hit.point.y, hit.point.z);
	ray.direction = ft_normalize_vec3(ray.direction);
	if (trace(&ray, scene, &new_hit, 2) == TRUE)
		return (1);
	return (0);
}

static t_rgba	shade(t_scene *scene, t_raycast_hit *hit)
{
	t_rgba		c;
	size_t		i;
	size_t		shadow;
	double		d;
	
	i = 0;
	shadow = 0;
	d = 0;
	if (hit->shape)
	{
		c = hit->shape->color;
		// if (hit->shape->type == MODEL)
		// {
		// 	c = ft_make_rgba(hit->normal.x * 0.5 + 0.5, hit->normal.y * 0.5 + 0.5, hit->normal.z * 0.5 + 0.5, 1.0);
		// //	t_rgba c = ft_make_rgba(1.0- ft_inv_lerp_d(hit->distance, 4, 6), 0, 0, 1);
		// 	return (c);
		// }
		while ( i < scene->num_lights)
		{
			shadow = in_shadow(scene->lights[i], *hit, scene);
			if (shadow == 1)
				return (ft_make_rgba(0, 0, 0, 1.0)); // vaihda laskukaavaan
			if (shadow == 0)
			{
				d += spot_shading(scene->lights[i], *hit, scene);
			}
			i++;
		}
		if (scene->help_ray == 1)
			ft_printf("color times %f\n", d); //
		c = ft_mul_rgba(c, d);
		return (c);
	}
	return (ft_make_rgba(0.1, 0.1, 0.1, 1.0));
}

static void		init_hit_info(t_raycast_hit *hit)
{
	hit->shape = NULL;
}

t_rgba			raycast(t_ray *ray, t_scene *scene)
{
	t_rgba color;
	t_raycast_hit hit;
	init_hit_info(&hit);

	color = ft_make_rgba(0.2, 0.2, 0.2, 1.0); // ambient
	if (trace(ray, scene, &hit, FALSE) != FALSE)
	{
		// laske normaali ja muu hit info  
		hit.normal = calc_hit_normal(&hit);
		color = shade(scene, &hit);
	}
	return (ft_clamp_rgba(color));
}
