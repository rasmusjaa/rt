/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:38:03 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/30 15:17:32 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCTREE_H
# define OCTREE_H

# include "mesh.h"
# include "bounds.h"

# define NUM_CHILDREN 8

# define BOTTOM_LEFT_FRONT		0
# define BOTTOM_RIGHT_FRONT		1
# define BOTTOM_RIGHT_BACK		2
# define BOTTOM_LEFT_BACK		3
# define TOP_LEFT_FRONT			4
# define TOP_RIGHT_FRONT		5
# define TOP_RIGHT_BACK			6
# define TOP_LEFT_BACK			7

typedef struct	s_octree_content
{
	void					*data;
	size_t					data_size;
	struct s_octree_content	*next;
}				t_octree_content;

typedef struct	s_octree
{
	struct s_octree		*parent;
	struct s_octree		*children[NUM_CHILDREN];
	t_bounds			child_bounds[NUM_CHILDREN];
	size_t				num_tris;
	t_triface			*contains_trifaces;
	t_bounds			bounds;
	int					is_last;
}				t_octree;

t_octree		*octree_create_node(t_bounds bounds, size_t num_tris,
					t_triface *trifaces);
void			octree_destroy(t_octree *o);

#endif
