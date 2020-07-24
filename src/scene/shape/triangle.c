/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:38:15 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/23 14:31:14 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "libft.h"

int intersects_triangle(t_ray *ray, t_triface *triface, t_raycast_hit *hit)
{
	t_vec3	p0;
	t_vec3	p1;
	t_vec3	p2;
	double	d;

	d = ft_dot_vec3(triface->normal, ray->direction);
	if (ft_abs_d(d) < EPSILON)
		return (FALSE);
	hit->t = ft_dot_vec3(ft_sub_vec3(triface->v[0], ray->origin), triface->normal) / d;
	if (hit->t < MIN_CLIP || hit->t > MAX_CLIP)
		return (FALSE);
	hit->point = ft_add_vec3(ray->origin, ft_mul_vec3(ray->direction, hit->t));

	p0 = ft_sub_vec3(hit->point, triface->v[0]);
	p1 = ft_sub_vec3(hit->point, triface->v[1]);
	p2 = ft_sub_vec3(hit->point, triface->v[2]);

	if (ft_dot_vec3(triface->normal, ft_cross_vec3(triface->e[0], p0)) >= 0 &&
		ft_dot_vec3(triface->normal, ft_cross_vec3(triface->e[1], p1)) >= 0 &&
		ft_dot_vec3(triface->normal, ft_cross_vec3(triface->e[2], p2)) >= 0)
	{
		hit->distance = hit->t;
		hit->normal = triface->normal;
		return (TRUE);
	}
	return (FALSE);
}
