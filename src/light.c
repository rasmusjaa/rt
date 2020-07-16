/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:48:51 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/16 17:58:40 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		in_shadow(t_light light, t_raycast_hit hit, t_scene *scene)
{
	t_ray			shadow_ray;
	t_raycast_hit	new_hit;

	shadow_ray.origin = ft_add_vec3(hit.point, ft_mul_vec3(hit.normal, EPSILON));
	shadow_ray.direction = ft_sub_vec3(light.position, hit.point);
	new_hit.light_dist = ft_len_vec3(shadow_ray.direction);
	if (scene->help_ray)
		ft_printf("testing shadow of %f %f %f\n", hit.point.x, hit.point.y, hit.point.z);
	shadow_ray.direction = ft_normalize_vec3(shadow_ray.direction);
	return (trace(&shadow_ray, scene, &new_hit, 1));
}

double	calc_shadow(t_light light, t_raycast_hit hit, t_scene *scene)
{
	int i;
	int num_samples;
	double s;
	t_ray			shadow_ray;
	t_raycast_hit	new_hit;
	t_vec3 lr = ft_normalize_vec3(ft_cross_vec3(ft_sub_vec3(hit.point, light.position), ft_make_vec3(0,1,0)));

	s = 0;
	num_samples = light.leds;
	i = 0;
	while (i < num_samples)
	{
		t_vec3 lp = ft_add_vec3(light.position, ft_mul_vec3(ft_rotate_vec3(lr, ft_make_vec3(0, i * (360.0/num_samples), 0)), light.radius));
		shadow_ray.origin = ft_add_vec3(hit.point, ft_mul_vec3(hit.normal, EPSILON));
		shadow_ray.direction = ft_sub_vec3(lp, hit.point);
		new_hit.light_dist = ft_len_vec3(shadow_ray.direction);
		shadow_ray.direction = ft_normalize_vec3(shadow_ray.direction);
		if (trace(&shadow_ray, scene, &new_hit, 1) && hit.shape != new_hit.shape)
			s += 1.0 / num_samples;
		i++;
	}
	return (s);
}
