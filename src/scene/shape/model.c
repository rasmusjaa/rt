/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:31:38 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 16:02:05 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "raycast.h"

int		intersects_last_octree(t_ray *ray, t_shape *model,
	t_octree *node, t_raycast_hit *hit)
{
	size_t			i;
	int				hit_found;
	t_raycast_hit	cur_hit;

	i = 0;
	cur_hit.distance = INFINITY;
	hit_found = FALSE;
	while (i < node->num_tris)
	{
		if (intersects_triangle(ray, &(node->contains_trifaces[i]), &cur_hit))
		{
			if (cur_hit.distance < hit->distance)
			{
				cur_hit.shape = model;
				cur_hit.triface = &node->contains_trifaces[i];
				*hit = cur_hit;
				hit_found = TRUE;
			}
		}
		i++;
	}
	return (hit_found);
}

int		intersects_octree_model(t_ray *ray, t_shape *model,
	t_octree *node, t_raycast_hit *hit)
{
	size_t			i;
	t_raycast_hit	cur_hit;
	int				hit_found;

	if (!intersects_bounds(ray, &(node->bounds)))
		return (FALSE);
	if (node->is_last)
		return (intersects_last_octree(ray, model, node, hit));
	cur_hit.distance = INFINITY;
	hit_found = FALSE;
	i = 0;
	while (i < NUM_CHILDREN)
	{
		if (intersects_octree_model(ray, model, node->children[i], &cur_hit))
		{
			if (cur_hit.distance < hit->distance)
			{
				*hit = cur_hit;
				hit_found = TRUE;
			}
		}
		i++;
	}
	return (hit_found);
}
