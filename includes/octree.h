/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:38:03 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/09 14:31:06 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCTREE_H
# define OCTREE_H

# include "mesh.h"

# define NUM_CHILDREN 8

# define TOP_LEFT_FRONT			1<<0
# define TOP_RIGHT_FRONT		1<<1
# define BOTTOM_LEFT_FRONT		1<<2
# define BOTTOM_RIGHT_FRONT		1<<3
# define TOP_LEFT_BACK			1<<4
# define TOP_RIGHT_BACK			1<<5
# define BOTTOM_LEFT_BACK		1<<6
# define BOTTOM_RIGHT_BACK		1<<7
# define ACTIVE_NONE			0

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
	t_octree_content	*content;
	t_bounds			bounds;
	unsigned char		active_children;
}				t_octree;


t_octree		*octree_create_node(t_octree_content *content);
t_octree_content *octree_content_create(void *data, size_t data_size);

#endif
