/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:31:34 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 16:01:22 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "bounds.h"
#include "libft.h"
#include "shape.h"
#include "raycast.h"

/*
** mesh bounds are calculated on load
** axis aligned
*/

int	intersects_bounds(t_ray *ray, t_bounds *b)
{
	double	tx[2];
	double	ty[2];
	double	tz[2];

	tx[0] = (b->min.x - ray->origin.x) / ray->direction.x;
	tx[1] = (b->max.x - ray->origin.x) / ray->direction.x;
	if (tx[0] > tx[1])
		ft_swap_d(&tx[0], &tx[1]);
	ty[0] = (b->min.y - ray->origin.y) / ray->direction.y;
	ty[1] = (b->max.y - ray->origin.y) / ray->direction.y;
	if (ty[0] > ty[1])
		ft_swap_d(&ty[0], &ty[1]);
	if ((tx[0] > ty[1]) || (ty[0] > tx[1]))
		return (FALSE);
	tz[0] = (b->min.z - ray->origin.z) / ray->direction.z;
	tz[1] = (b->max.z - ray->origin.z) / ray->direction.z;
	if (tz[0] > tz[1])
		ft_swap_d(&tz[0], &tz[1]);
	if ((tx[0] > tz[1]) || (tz[0] > tx[1]))
		return (FALSE);
	if ((ty[0] > tz[1]) || (tz[0] > ty[1]))
		return (FALSE);
	return (TRUE);
}

int	point_inside_bounds(t_vec3 p, t_shape *shape)
{
	if (p.x < shape->bounds.min.x || p.x > shape->bounds.max.x)
		return (FALSE);
	if (p.y < shape->bounds.min.y || p.y > shape->bounds.max.y)
		return (FALSE);
	if (p.z < shape->bounds.min.z || p.z > shape->bounds.max.z)
		return (FALSE);
	return (TRUE);
}

int	inside_bounds(t_bounds object_bounds, t_bounds bounds)
{
	if ((bounds.min.x < object_bounds.min.x &&
		bounds.max.x < object_bounds.min.x) ||
		(bounds.min.x > object_bounds.max.x &&
		bounds.max.x > object_bounds.max.x))
		return (FALSE);
	if ((bounds.min.y < object_bounds.min.y &&
		bounds.max.y < object_bounds.min.y) ||
		(bounds.min.y > object_bounds.max.y &&
		bounds.max.y > object_bounds.max.y))
		return (FALSE);
	if ((bounds.min.z < object_bounds.min.z &&
		bounds.max.z < object_bounds.min.z) ||
		(bounds.min.z > object_bounds.max.z &&
		bounds.max.z > object_bounds.max.z))
		return (FALSE);
	return (TRUE);
}
