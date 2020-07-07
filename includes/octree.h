/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:38:03 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/07 19:20:44 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCTREE_H
# define OCTREE_H

# define NUM_CHILDREN 8

typedef struct	s_octree
{
	struct s_octree	*children[NUM_CHILDREN];
	char		*content;
}				t_octree;


t_octree	*octree_create_node(char *content);

#endif
