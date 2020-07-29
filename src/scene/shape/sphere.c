/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:19:26 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/29 17:08:16 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "libft.h"
#include "texture.h"

t_vec3	calc_hit_normal_sphere(t_shape *sphere, t_raycast_hit *hit)
{
	return (ft_normalize_vec3(ft_sub_vec3(hit->point, sphere->position)));
}

t_vec2	calc_hit_uv_sphere(t_shape *sphere, t_raycast_hit *hit)
{
	double u;
	double v;
	t_vec3 n;

	n = ft_rotate_vec3(hit->normal, sphere->rotation);
	u = atan2(n.x, n.z) / (2.0 * M_PI) + 0.5;
	v = n.y / 2.0 + 0.5;
	return (ft_make_vec2(u, v));
}

int		intersects_bump_sphere(t_ray *ray, t_shape *sphere,
	t_raycast_hit *hit, t_vec2 uv)
{
	t_quadratic	q;
	t_vec3		oc;
	double		temp;
	t_texture	*tex;

	tex = get_texture_by_id(ray->scene, sphere->material->bump_tex_id);
	temp = ft_intensity_rgba(sample_texture(tex, uv))
		* sphere->material->bump_mult;
	temp = sphere->radius - temp;
	oc = ft_sub_vec3(ray->origin, sphere->position);
	q.a = ft_dot_vec3(ray->direction, ray->direction);
	q.b = 2.0 * ft_dot_vec3(oc, ray->direction);
	q.c = ft_dot_vec3(oc, oc) - (temp * temp);
	if (solve_quadratic(q, &hit->t, &hit->t2) > 0)
	{
		if ((hit->t > hit->t2 || hit->t < MIN_CLIP) && hit->t2 > MIN_CLIP)
			ft_swap_d(&hit->t, &hit->t2);
		if (hit->t > MAX_CLIP || hit->t < MIN_CLIP)
			return (FALSE);
		hit->point = point_on_ray(ray, hit->t);
		hit->distance = hit->t;
		return (TRUE);
	}
	return (FALSE);
}

int		prep_bump(t_ray *ray, t_shape *sphere, t_raycast_hit *hit)
{
	hit->normal = calc_hit_normal_sphere(sphere, hit);
	ray->uv = calc_hit_uv_sphere(sphere, hit);
	return (intersects_bump_sphere(ray, sphere, hit, ray->uv));
}

int		intersects_sphere(t_ray *ray, t_shape *sphere, t_raycast_hit *hit)
{
	t_quadratic	q;
	t_vec3		oc;
	double		temp;

	temp = sphere->radius + sphere->material->explode
		* ft_inv_lerp_d((double)rand(), 0, RAND_MAX);
	oc = ft_sub_vec3(ray->origin, sphere->position);
	q.a = ft_dot_vec3(ray->direction, ray->direction);
	q.b = 2.0 * ft_dot_vec3(oc, ray->direction);
	q.c = ft_dot_vec3(oc, oc) - (temp * temp);
	if (solve_quadratic(q, &hit->t, &hit->t2) > 0)
	{
		if ((hit->t > hit->t2 || hit->t < MIN_CLIP) && hit->t2 > MIN_CLIP)
			ft_swap_d(&hit->t, &hit->t2);
		if (hit->t > MAX_CLIP || hit->t < MIN_CLIP)
			return (FALSE);
		hit->point = point_on_ray(ray, hit->t);
		hit->distance = hit->t;
		if (sphere->material->bump_tex_id && get_texture_by_id(
			ray->scene, sphere->material->bump_tex_id)->img_data != NULL)
			return (prep_bump(ray, sphere, hit));
		return (TRUE);
	}
	return (FALSE);
}
