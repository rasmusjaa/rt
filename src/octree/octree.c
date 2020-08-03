/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:41:21 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 12:53:08 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rt.h"
#include "octree.h"
#include "vector.h"
#include "ft_printf.h"

void		octree_calc_child_bounds(t_octree *node)
{
	t_vec3		half;
	t_vec3		center;
	t_bounds	nb;
	t_bounds	*b;

	nb = node->bounds;
	b = node->child_bounds;
	half = ft_mul_vec3(ft_sub_vec3(nb.max, nb.min), 0.5);
	center = ft_add_vec3(nb.min, half);
	b[BOTTOM_LEFT_FRONT].min = nb.min;
	b[BOTTOM_LEFT_FRONT].max = center;
	b[BOTTOM_RIGHT_FRONT].min = ft_make_vec3(center.x, nb.min.y, nb.min.z);
	b[BOTTOM_RIGHT_FRONT].max = ft_make_vec3(nb.max.x, center.y, center.z);
	b[BOTTOM_RIGHT_BACK].min = ft_make_vec3(center.x, nb.min.y, center.z);
	b[BOTTOM_RIGHT_BACK].max = ft_make_vec3(nb.max.x, center.y, nb.max.z);
	b[BOTTOM_LEFT_BACK].min = ft_make_vec3(nb.min.x, nb.min.y, center.z);
	b[BOTTOM_LEFT_BACK].max = ft_make_vec3(center.x, center.y, nb.max.z);
	b[TOP_LEFT_FRONT].min = ft_make_vec3(nb.min.x, center.y, nb.min.z);
	b[TOP_LEFT_FRONT].max = ft_make_vec3(center.x, nb.max.y, center.z);
	b[TOP_RIGHT_FRONT].min = ft_make_vec3(center.x, center.y, nb.min.z);
	b[TOP_RIGHT_FRONT].max = ft_make_vec3(nb.max.x, nb.max.y, center.z);
	b[TOP_RIGHT_BACK].min = center;
	b[TOP_RIGHT_BACK].max = nb.max;
	b[TOP_LEFT_BACK].min = ft_make_vec3(nb.min.x, center.y, center.z);
	b[TOP_LEFT_BACK].max = ft_make_vec3(center.x, nb.max.y, nb.max.z);
}

t_octree	*octree_create_children(t_octree *node, t_bounds bounds)
{
	size_t		i;
	double		bound_len;

	i = 0;
	bound_len = ft_len_vec3(ft_sub_vec3(bounds.max, bounds.min));
	if (node->num_tris > 10 && bound_len > 0.1)
	{
		octree_calc_child_bounds(node);
		while (i < 8)
		{
			node->children[i] = octree_create_node(node->child_bounds[i],
				node->num_tris, node->contains_trifaces);
			i++;
		}
	}
	else
		node->is_last = TRUE;
	return (node);
}

t_octree	*octree_create_node(t_bounds bounds, size_t num_tris,
	t_triface *trifaces)
{
	t_octree	*node;
	size_t		i;
	size_t		j;

	node = NULL;
	if (!(node = (t_octree*)malloc(sizeof(t_octree))) ||
			!(node->contains_trifaces = (t_triface*)malloc(sizeof(t_triface)
			* num_tris)))
		exit_message("Octree_create_node: failed to malloc!\n");
	node->is_last = FALSE;
	node->bounds = bounds;
	i = 0;
	j = 0;
	while (i < num_tris)
	{
		if (inside_bounds(trifaces[i].bounds, bounds))
			node->contains_trifaces[j++] = trifaces[i];
		i++;
	}
	node->num_tris = j;
	return (octree_create_children(node, bounds));
}

void		octree_destroy(t_octree *o)
{
	int i;

	if (!o)
		return ;
	i = 0;
	if (!o->is_last)
	{
		while (i < NUM_CHILDREN)
			octree_destroy(o->children[i++]);
	}
	free(o->contains_trifaces);
	o->contains_trifaces = NULL;
	free(o);
	o = NULL;
}
