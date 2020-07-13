/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:38:03 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/09 19:49:33 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCTREE_H
# define OCTREE_H

# include "mesh.h"

# define FALSE 0
# define TRUE 1

# define NUM_CHILDREN 8

# define BOTTOM_LEFT_FRONT		0
# define BOTTOM_RIGHT_FRONT		1
# define BOTTOM_RIGHT_BACK		2
# define BOTTOM_LEFT_BACK		3
# define TOP_LEFT_FRONT			4
# define TOP_RIGHT_FRONT		5
# define TOP_RIGHT_BACK			6
# define TOP_LEFT_BACK			7
// # define ACTIVE_NONE			0

typedef struct	s_octree_content
{
	void		*data;
	size_t		data_size;
	struct s_octree_content *next;
}				t_octree_content;

typedef struct	s_octree
{
	struct s_octree		*parent;
	struct s_octree		*children[NUM_CHILDREN];
	t_bounds			child_bounds[NUM_CHILDREN];
	// t_octree_content	*content;
	size_t				num_tris;
	t_triface			*trifaces;
	t_triface			*contains_trifaces;
	t_bounds			bounds;
	int					is_last;
	// unsigned char		active_children;
}				t_octree;


t_octree	*octree_create_node(t_bounds bounds, size_t num_tris, t_triface *trifaces);
// t_octree_content *octree_content_create(void *data, size_t data_size);
// void			octree_insert(t_octree *octree, t_octree *child, unsigned char octant);
#endif
