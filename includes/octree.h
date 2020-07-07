/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:38:03 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/07 20:04:59 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCTREE_H
# define OCTREE_H

# include "mesh.h"

# define NUM_CHILDREN 8

typedef struct	s_octree_content
{
	void		*data;
	size_t		data_size;
	struct s_octree_content *next;
}				t_octree_content;

typedef struct	s_octree
{
	struct s_octree	*children[NUM_CHILDREN];
	t_octree_content	*content;
}				t_octree;


t_octree		*octree_create_node(t_octree_content *content);
t_octree_content *octree_content_create(void *data, size_t data_size);

#endif
