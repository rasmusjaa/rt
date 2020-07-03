/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:56:36 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/03 18:09:17 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "ft_printf.h"

t_mesh *mesh_create(void)
{
	t_mesh *m;

	if (!(m = (t_mesh*)malloc(sizeof(t_mesh))))
	{
		ft_printf("mesh_create: failed to allocate memory for t_mesh!\n");
		return (NULL);
	}
	m->num_vertices = 0;
	m->vertices = NULL;
	m->num_trifaces = 0;
	m->trifaces = NULL;
	m->num_normals = 0;
	m->normals = NULL;
	m->num_uvs = 0;
	m->uvs = NULL;
	return (m);
}

void	mesh_create_verts(t_mesh *m, size_t num_vertices)
{
	if (!m)
		return ;
	m->num_vertices = num_vertices;
	if (num_vertices == 0)
		return ;
	if (m->vertices)
		free(m->vertices);
	if (!(m->vertices = (t_vec3*)malloc(sizeof(t_vec3) * num_vertices)))
		ft_printf("mesh_create: failed to allocate memory for vertices!\n");
}

void	mesh_create_normals(t_mesh *m, size_t num_normals)
{
	if (!m)
		return ;
	m->num_normals = num_normals;
	if (num_normals == 0)
		return ;
	if (m->normals)
		free(m->normals);
	if (!(m->normals = (t_vec3*)malloc(sizeof(t_vec3) * num_normals)))
		ft_printf("mesh_create: failed to allocate memory for normals!\n");
}

void	mesh_create_uvs(t_mesh *m, size_t num_uvs)
{
	if (!m)
		return ;
	m->num_uvs = num_uvs;
	if (num_uvs == 0)
		return ;
	if (m->uvs)
		free(m->uvs);
	if (!(m->uvs = (t_vec2*)malloc(sizeof(t_vec2) * num_uvs)))
		ft_printf("mesh_create: failed to allocate memory for uvs!\n");
}

void	mesh_create_trifaces(t_mesh *m, size_t num_trifaces)
{
	if (!m)
		return ;
	if (m->trifaces)
		free(m);
	m->num_trifaces = num_trifaces;
	if (num_trifaces == 0)
		return ;
	if (!(m->trifaces = (t_triface*)malloc(sizeof(t_triface) * num_trifaces)))
		ft_printf("mesh_create: failed to allocate memory for faces!\n");
}

void	mesh_destroy(t_mesh *m)
{
	m->num_vertices = 0;
	m->num_trifaces = 0;
	free(m->vertices);
	free(m->trifaces);
	free(m);
}

void	mesh_set_vert(t_mesh *m, size_t i, t_vec3 v)
{
	if (!m || !m->vertices || i > m->num_vertices - 1)
		ft_printf("mesh_set_vert: failed to set vertex!\n");
	else
		m->vertices[i] = v;
}
