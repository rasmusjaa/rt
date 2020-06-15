/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:46:47 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/15 13:09:33 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	intersects_sphere(t_ray *ray, t_shape *shape, t_raycast_hit *hit)
{
	ray = 0;
	shape = 0;
	hit = 0;
	return (TRUE);
}

int	intersects_shape(t_ray *ray, t_shape *shape, t_raycast_hit *hit)
{
	ray = 0;
	shape = 0;
	hit = 0;
	// select function from shape->type (function pointer?)
	if (shape->type == SPHERE)
		return (intersects_sphere(ray, shape, hit));
	// populate hit info
	return (FALSE);
}
