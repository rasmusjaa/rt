/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:41:21 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/09 14:53:55 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "octree.h"
#include "ft_printf.h"
#include <stdlib.h>

t_octree	*octree_create_node(t_octree_content *content)
{
	t_octree	*node;
	size_t		i;

	node = NULL;
	if (!(node = (t_octree*)malloc(sizeof(t_octree))))
	{
		ft_printf("octree_create_node: failed to allocate memory for octree!\n");
		return (NULL);
	}
	node->content = content;
	i = 0;

	while (i < NUM_CHILDREN)
	{
		node->children[i] = NULL;
		i++;
	}
	node->parent = NULL;
	node->active_children = ACTIVE_NONE;
	return (node);
}

void	octree_calc_bounds(t_octree *octree)
{
	if (!octree || !octree->parent)
		return ;

}

void	octree_insert(t_octree *parent, t_octree *child, unsigned char octant)
{
	if (!parent || !child)
}

t_octree_content *octree_content_create(void *data, size_t data_size)
{
	t_octree_content *oc;

	if (!(oc = (t_octree_content*)malloc(sizeof(t_octree_content))))
		return (NULL);
	oc->data_size = data_size;
	oc->data = data;
	oc->next = NULL;
	return (oc);
}
