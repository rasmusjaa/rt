/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:48:51 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/21 18:47:02 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

double		in_shadow(t_light light, t_raycast_hit hit, t_scene *scene)
{
	t_ray			shadow_ray;
	t_raycast_hit	new_hit;
	double			s;

	s = 0;
	shadow_ray.origin = ft_add_vec3(hit.point, ft_mul_vec3(hit.normal, EPSILON));
	shadow_ray.direction = ft_sub_vec3(light.position, hit.point);
	shadow_ray.source_shape = hit.shape;
	new_hit.light_dist = ft_len_vec3(shadow_ray.direction);
	new_hit.shape = NULL;
	shadow_ray.direction = ft_normalize_vec3(shadow_ray.direction);
	shadow_ray.shadow = 0;
	shadow_ray.is_shadow = TRUE;
	if (scene->help_ray)
		ft_printf("testing shadow of %f %f %f\n", hit.point.x, hit.point.y, hit.point.z);
	if (trace(&shadow_ray, scene, &new_hit))
	{
		s = shadow_ray.shadow;
	}
	return (s);
}

static	t_vec2 random_inside_circle(t_vec2 center, double radius)
{
	t_vec2 p;
	double r;
	double theta;

	r = radius * sqrt((double)rand() / RAND_MAX * 2.0);
	theta = ((double)rand() / RAND_MAX * 2.0) * 2 * M_PI;
	p.x = center.x + r * cos(theta);
	p.y = center.y + r * sin(theta);
	return (p);
}

double	calc_shadow(t_light light, t_raycast_hit hit, t_scene *scene)
{
	int i;
	int num_samples;
	double s;
	t_ray			shadow_ray;
	t_raycast_hit	new_hit;
//	t_vec3 lr = ft_normalize_vec3(ft_cross_vec3(ft_sub_vec3(hit.point, light.position), ft_make_vec3(0,1,0)));

	if (light.radius < 1)
		return (in_shadow(light, hit, scene));
	s = 0;
	num_samples = light.leds;
	i = 0;
	while (i < num_samples)
	{
		t_vec2 rnd = random_inside_circle(ft_make_vec2(0,0), light.radius);
		// t_vec3 lp = ft_add_vec3(light.position, ft_mul_vec3(ft_rotate_vec3(lr, ft_make_vec3(0, i * (360.0/num_samples), 0)), light.radius));
		t_vec3 lp = ft_add_vec3(light.position, ft_make_vec3(rnd.x, rnd.y, 0));

		shadow_ray.origin = ft_add_vec3(hit.point, ft_mul_vec3(hit.normal, EPSILON));
		shadow_ray.direction = ft_sub_vec3(lp, hit.point);
		shadow_ray.source_shape = hit.shape;
		new_hit.light_dist = ft_len_vec3(shadow_ray.direction);
		new_hit.shape = NULL;
		shadow_ray.direction = ft_normalize_vec3(shadow_ray.direction);
		if (trace(&shadow_ray, scene, &new_hit))
			s += (1.0 / num_samples) * shadow_ray.shadow;;
		i++;
	}
	return (s);
}
