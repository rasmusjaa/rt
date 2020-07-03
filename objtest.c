/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objtest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 17:27:02 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/03 18:22:40 by wkorande         ###   ########.fr       */
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
	while (i < m->num_uvs)
	{
		printf("%zu vt %f %f\n", i, m->uvs[i].x, m->uvs[i].y);
		i++;
	}

	i = 0;
	while (i < m->num_normals)
	{
		printf("%zu vn %f %f %f\n", i, m->normals[i].x, m->normals[i].y, m->normals[i].z);
		i++;
	}

	i = 0;
	while (i < m->num_trifaces)
	{
		printf("%zu f %f %f %f ", i, m->trifaces[i].v[0].x, m->trifaces[i].v[0].y, m->trifaces[i].v[0].z);
		printf("/ %f %f ", m->trifaces[i].uv[0].x, m->trifaces[i].uv[0].y);
		printf("/ %f %f %f\n", m->trifaces[i].n[0].x, m->trifaces[i].n[0].y, m->trifaces[i].n[0].z);
		i++;
	}

	return (0);
}
