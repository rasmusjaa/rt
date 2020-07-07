/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objtest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 17:27:02 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/06 13:27:45 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include <stdio.h>

t_mesh	*obj_load(const char *filename);

int main(void)
{
	t_mesh *m = obj_load("monkey.obj");

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
		printf("/ %f %f %f ", m->trifaces[i].n[0].x, m->trifaces[i].n[0].y, m->trifaces[i].n[0].z);

		printf("\t%zu f %f %f %f ", i, m->trifaces[i].v[1].x, m->trifaces[i].v[1].y, m->trifaces[i].v[1].z);
		printf("/ %f %f ", m->trifaces[i].uv[1].x, m->trifaces[i].uv[1].y);
		printf("/ %f %f %f ", m->trifaces[i].n[1].x, m->trifaces[i].n[1].y, m->trifaces[i].n[1].z);

		printf("\t%zu f %f %f %f ", i, m->trifaces[i].v[2].x, m->trifaces[i].v[2].y, m->trifaces[i].v[2].z);
		printf("/ %f %f ", m->trifaces[i].uv[2].x, m->trifaces[i].uv[2].y);
		printf("/ %f %f %f\n", m->trifaces[i].n[2].x, m->trifaces[i].n[2].y, m->trifaces[i].n[2].z);
		i++;
	}

	mesh_calc_bounds(m);

	printf("bounds min %f %f %f\n", m->bounds.min.x, m->bounds.min.y, m->bounds.min.z);
	printf("bounds max %f %f %f\n", m->bounds.max.x, m->bounds.max.y, m->bounds.max.z);

	mesh_destroy(m);

	return (0);
}