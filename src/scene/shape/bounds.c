/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:31:34 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/29 17:56:29 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "bounds.h"
#include "libft.h"

/*
** mesh bounds are calculated on load
** axis aligned
*/
int	intersects_bounds(t_ray *ray, t_bounds *b, int debug)
{
	// might have to add that if camera is in bounding box return true
	double txmin = (b->min.x - ray->origin.x) / ray->direction.x;
	double txmax = (b->max.x - ray->origin.x) / ray->direction.x;

	// need to swap if we are looking from behind, as is only works if camera pos in front of bounds
	if (txmin > txmax)
		ft_swap_d(&txmin, &txmax);

	double tymin = (b->min.y - ray->origin.y) / ray->direction.y;
	double tymax = (b->max.y - ray->origin.y) / ray->direction.y;

	if (tymin > tymax)
		ft_swap_d(&tymin, &tymax);

	if ((txmin > tymax) || (tymin > txmax))
		return (FALSE);

	double tzmin = (b->min.z - ray->origin.z) / ray->direction.z;
	double tzmax = (b->max.z - ray->origin.z) / ray->direction.z;

	if (tzmin > tzmax)
		ft_swap_d(&tzmin, &tzmax);

	if ((txmin > tzmax) || (tzmin > txmax))
		return (FALSE);

	if ((tymin > tzmax)  || (tzmin > tymax))
		return (FALSE);
	return (TRUE);
	if (debug)
		return (TRUE);
}

int			point_inside_bounds(t_vec3 p, t_bounds bounds)
{
	if (p.x < bounds.min.x || p.x > bounds.max.x)
		return (FALSE);
	if (p.y < bounds.min.y || p.y > bounds.max.y)
		return (FALSE);
	if (p.z < bounds.min.z || p.z > bounds.max.z)
		return (FALSE);
	return (TRUE);
}

int			inside_bounds(t_bounds object_bounds, t_bounds bounds)
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
