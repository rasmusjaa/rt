/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:38:03 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/07 18:57:51 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCTREE_H
# define OCTREE_H

# define NUM_CHILDREN 8

typedef struct	s_octree
{
	t_octree	*children[NUM_CHILDREN];
	void		*content;
}				t_octree;


t_octree	*octree_create_node(void *content);

#endif
