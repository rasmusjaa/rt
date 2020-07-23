/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:41:21 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/23 22:58:51 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rt.h"
#include "octree.h"
#include "vector.h"
#include "ft_printf.h"

void	octree_calc_child_bounds(t_octree *node)
{
	t_vec3		dimensions;
	t_vec3		half;
	t_vec3		center;
	t_bounds	nb;
	t_bounds	*b;

	if (!node)
		exit_message("Octree_calc_bounds: node is null!\n");
	nb = node->bounds;
	b = node->child_bounds;
	dimensions = ft_sub_vec3(nb.max, nb.min);
	half = ft_mul_vec3(dimensions, 0.5);
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
	node->num_tris = num_tris;
	i = 0;
	j = 0;
	while (i < num_tris)
	{
		if (inside_bounds(trifaces[i].bounds, bounds))
			node->contains_trifaces[j++] = trifaces[i];
		i++;
	}
	node->num_tris = j;
	i = 0;
	double bound_len = ft_len_vec3(ft_sub_vec3(bounds.max, bounds.min));
	if (j > 10 && bound_len > 0.1) // bound_len scenen mukaan?
	{
		octree_calc_child_bounds(node);
		while (i < 8)
		{
			node->children[i] = octree_create_node(node->child_bounds[i], j, node->contains_trifaces);
			i++;
		}
	}
	else
		node->is_last = TRUE;
	return (node);
}

void	octree_destroy(t_octree *o)
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



// void	octree_print_bounds(t_octree *node)
// {
// 	t_bounds *b;

// 	b = &node->bounds;
// 	ft_printf("HIT BOUNDING BOX\n");
// 	ft_printf("box xmin %f xmax %f ymin %f ymax %f zmin %f zmax %f\n",
// 	b->min.x, b->max.x, b->min.y, b->max.y, b->min.z, b->max.z);
// 	ft_printf("octant 0 xmin %f xmax %f ymin %f ymax %f zmin %f zmax %f\n",
// 	octant[0].min.x, octant[0].max.x, octant[0].min.y, octant[0].max.y, octant[0].min.z, octant[0].max.z);
// 	ft_printf("octant 1 xmin %f xmax %f ymin %f ymax %f zmin %f zmax %f\n",
// 	octant[1].min.x, octant[1].max.x, octant[1].min.y, octant[1].max.y, octant[1].min.z, octant[1].max.z);
// 	ft_printf("octant 2 xmin %f xmax %f ymin %f ymax %f zmin %f zmax %f\n",
// 	octant[2].min.x, octant[2].max.x, octant[2].min.y, octant[2].max.y, octant[2].min.z, octant[2].max.z);
// 	ft_printf("octant 3 xmin %f xmax %f ymin %f ymax %f zmin %f zmax %f\n",
// 	octant[3].min.x, octant[3].max.x, octant[3].min.y, octant[3].max.y, octant[3].min.z, octant[3].max.z);
// 	ft_printf("octant 4 xmin %f xmax %f ymin %f ymax %f zmin %f zmax %f\n",
// 	octant[4].min.x, octant[4].max.x, octant[4].min.y, octant[4].max.y, octant[4].min.z, octant[4].max.z);
// 	ft_printf("octant 5 xmin %f xmax %f ymin %f ymax %f zmin %f zmax %f\n",
// 	octant[5].min.x, octant[5].max.x, octant[5].min.y, octant[5].max.y, octant[5].min.z, octant[5].max.z);
// 	ft_printf("octant 6 xmin %f xmax %f ymin %f ymax %f zmin %f zmax %f\n",
// 	octant[6].min.x, octant[6].max.x, octant[6].min.y, octant[6].max.y, octant[6].min.z, octant[6].max.z);
// 	ft_printf("octant 7 xmin %f xmax %f ymin %f ymax %f zmin %f zmax %f\n",
// 	octant[7].min.x, octant[7].max.x, octant[7].min.y, octant[7].max.y, octant[7].min.z, octant[7].max.z);
// }

// void	octree_insert(t_octree *octree, t_octree *child, unsigned char octant)
// {
// 	int i;
// 	int pos;

// 	if (!octree || !child)
// 		return ;
// 	child->parent = octree;
// 	i = 1;
// 	pos = 0;
// 	while (!(i & octant))
// 	{
// 		i = i << 1;
// 		pos++;
// 	}
// 	octree->children[pos] = child;
// 	octree->active_children |= octant;
// }

// t_octree_content *octree_content_create(void *data, size_t data_size)
// {
// 	t_octree_content *oc;

// 	if (!(oc = (t_octree_content*)malloc(sizeof(t_octree_content))))
// 		return (NULL);
// 	oc->data_size = data_size;
// 	oc->data = data;
// 	oc->next = NULL;
// 	return (oc);
// }
