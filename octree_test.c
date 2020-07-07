/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:55:12 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/07 19:27:08 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "octree.h"
#include <stdlib.h>

int main(void)
{
	t_octree *o;

	o = octree_create_node(NULL);

	o->children[0] = octree_create_node("hello");
}
