/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:48:51 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/14 16:49:19 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		in_shadow(t_light light, t_raycast_hit hit, t_scene *scene)
{
	t_ray			shadow_ray;
	t_raycast_hit	new_hit;

	shadow_ray.origin = hit.point;
	shadow_ray.direction = ft_sub_vec3(light.position, hit.point);
	new_hit.light_dist = ft_len_vec3(shadow_ray.direction);
	if (scene->help_ray)
		ft_printf("testing shadow of %f %f %f\n", hit.point.x, hit.point.y, hit.point.z);
	shadow_ray.direction = ft_normalize_vec3(shadow_ray.direction);
	return (trace(&shadow_ray, scene, &new_hit, 2));
}
