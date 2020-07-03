/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objtest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 17:27:02 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/03 17:53:37 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include <stdio.h>

t_mesh	*obj_load(const char *filename);

int main(void)
{
	t_mesh *m = obj_load("test.obj");

	size_t i;

	i = 0;
	while (i < m->num_vertices)
	{
		printf("%zu v %f %f %f\n", i, m->vertices[i].x, m->vertices[i].y, m->vertices[i].z);
		i++;
	}

	i = 0;
	while (i < m->num_trifaces)
	{
		printf("%zu f %f %f %f\n", i, m->trifaces[i].v[0].x, m->trifaces[i].v[0].y, m->trifaces[i].v[0].z);
		i++;
	}

	return (0);
}
