/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:41:21 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/07 18:50:23 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "octree.h"
#include "ft_printf.h"
#include <stdlib.h>

t_octree	*octree_create_node(void *content)
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
	return (node);
}
