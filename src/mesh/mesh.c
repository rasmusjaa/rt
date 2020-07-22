/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:56:36 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/09 13:46:35 by wkorande         ###   ########.fr       */
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
	m->bounds.min = ft_make_vec3(MAX_BOUNDS, MAX_BOUNDS, MAX_BOUNDS);
	m->bounds.max = ft_make_vec3(MIN_BOUNDS, MIN_BOUNDS, MIN_BOUNDS);
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
	{
		ft_printf("mesh_create: failed to allocate memory for vertices!\n");
		exit(EXIT_FAILURE);
	}
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
	{
		ft_printf("mesh_create: failed to allocate memory for normals!\n");
		exit(EXIT_FAILURE);
	}
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
	{
		ft_printf("mesh_create: failed to allocate memory for uvs!\n");
		exit(EXIT_FAILURE);
	}
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
	{
		ft_printf("mesh_create: failed to allocate memory for faces!\n");
		exit(EXIT_FAILURE);
	}
}

void	mesh_destroy(t_mesh *m)
{
	m->num_vertices = 0;
	m->num_trifaces = 0;
	m->num_normals = 0;
	m->num_uvs = 0;
	free(m->vertices);
	free(m->trifaces);
	free(m->normals);
	free(m->uvs);
	free(m);
}

void	mesh_set_vert(t_mesh *m, size_t i, t_vec3 v)
{
	if (!m || !m->vertices || i > m->num_vertices - 1)
	{
		ft_printf("mesh_set_vert: failed to set vertex!\n");
		exit(EXIT_FAILURE);
	}
	else
		m->vertices[i] = v;
}

void	mesh_calc_bounds(t_mesh *m)
{
	size_t i;

	m->bounds.min = ft_make_vec3(MAX_BOUNDS, MAX_BOUNDS, MAX_BOUNDS);
	m->bounds.max = ft_make_vec3(MIN_BOUNDS, MIN_BOUNDS, MIN_BOUNDS);
	i = 0;
	while (i < m->num_vertices)
	{
		if (m->vertices[i].x < m->bounds.min.x)
			m->bounds.min.x = m->vertices[i].x;
		if (m->vertices[i].y < m->bounds.min.y)
			m->bounds.min.y = m->vertices[i].y;
		if (m->vertices[i].z < m->bounds.min.z)
			m->bounds.min.z = m->vertices[i].z;

		if (m->vertices[i].x > m->bounds.max.x)
			m->bounds.max.x = m->vertices[i].x;
		if (m->vertices[i].y > m->bounds.max.y)
			m->bounds.max.y = m->vertices[i].y;
		if (m->vertices[i].z > m->bounds.max.z)
			m->bounds.max.z = m->vertices[i].z;
		i++;
	}
}
