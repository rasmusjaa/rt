/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:29:42 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/13 14:31:19 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "octree.h"

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
