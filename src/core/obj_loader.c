/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:05:05 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 12:17:24 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "ft_get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include "rt.h"
#include "shape.h"
#include "ft_printf.h"

static void	read_mesh_info(t_mesh *m, const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) == -1)
		exit_message("Error loading model file!");
	while (ft_get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "v ", 2) == 0)
			m->num_vertices++;
		else if (ft_strncmp(line, "vt", 2) == 0)
			m->num_uvs++;
		else if (ft_strncmp(line, "vn", 2) == 0)
			m->num_normals++;
		else if (ft_strncmp(line, "f ", 2) == 0)
			m->num_trifaces++;
		free(line);
	}
	close(fd);
	mesh_create_verts(m, m->num_vertices);
	mesh_create_normals(m, m->num_normals);
	mesh_create_uvs(m, m->num_uvs);
	mesh_create_trifaces(m, m->num_trifaces);
}

void		triface_calc_bounds(t_triface *t)
{
	size_t i;

	t->bounds.min = ft_make_vec3(MAX_BOUNDS, MAX_BOUNDS, MAX_BOUNDS);
	t->bounds.max = ft_make_vec3(MIN_BOUNDS, MIN_BOUNDS, MIN_BOUNDS);
	i = 0;
	while (i < 3)
	{
		if (t->v[i].x < t->bounds.min.x)
			t->bounds.min.x = t->v[i].x;
		if (t->v[i].y < t->bounds.min.y)
			t->bounds.min.y = t->v[i].y;
		if (t->v[i].z < t->bounds.min.z)
			t->bounds.min.z = t->v[i].z;
		if (t->v[i].x > t->bounds.max.x)
			t->bounds.max.x = t->v[i].x;
		if (t->v[i].y > t->bounds.max.y)
			t->bounds.max.y = t->v[i].y;
		if (t->v[i].z > t->bounds.max.z)
			t->bounds.max.z = t->v[i].z;
		i++;
	}
}

static void	parse_face(t_mesh *m, size_t i, char *line, size_t j)
{
	char	**parts;
	char	**tf;
	size_t	n;

	parts = ft_strsplit(line + 1, ' ');
	while (parts[j] && (tf = ft_strsplit(parts[j], '/')))
	{
		if (!tf[0] || ((n = ft_atoi(tf[0])) && (n > m->num_vertices || n < 1)))
			exit_message("Not enough model vertices");
		m->trifaces[i].v[j] = m->vertices[n - 1];
		if (!tf[1] || ((n = ft_atoi(tf[1])) && (n > m->num_uvs || n < 1)))
			exit_message("Not enough model textures");
		m->trifaces[i].uv[j] = m->uvs[n - 1];
		if (!tf[2] || ((n = ft_atoi(tf[2])) && (n > m->num_normals || n < 1)))
			exit_message("Not enough model normals");
		m->trifaces[i].n[j] = m->normals[n - 1];
		free_null(5, tf[0], tf[1], tf[2], tf, parts[j]);
		j++;
	}
	free(parts);
	m->trifaces[i].e[0] = ft_sub_vec3(m->trifaces[i].v[1], m->trifaces[i].v[0]);
	m->trifaces[i].e[1] = ft_sub_vec3(m->trifaces[i].v[2], m->trifaces[i].v[1]);
	m->trifaces[i].e[2] = ft_sub_vec3(m->trifaces[i].v[0], m->trifaces[i].v[2]);
	m->trifaces[i].normal = m->trifaces[i].n[0];
	triface_calc_bounds(&m->trifaces[i]);
}

void		read_mesh(int fd, t_mesh *m, t_shape shape)
{
	char	*line;
	size_t	i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	while (ft_get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "v ", 2) == 0)
			m->vertices[i[0]++] = ft_rotate_vec3(ft_mul_vec3(ft_add_vec3(
				ft_parse_vec3(line + 1), shape.position), shape.scale),
				shape.rotation);
		else if (ft_strncmp(line, "vt", 2) == 0)
			m->uvs[i[1]++] = ft_parse_vec2(line + 1);
		else if (ft_strncmp(line, "vn", 2) == 0)
			m->normals[i[2]++] = ft_rotate_vec3(ft_parse_vec3(line + 2),
				shape.rotation);
		else if (ft_strncmp(line, "f ", 2) == 0)
			parse_face(m, i[3]++, line, 0);
		free(line);
	}
}

t_mesh		*obj_load(const char *filename, t_shape shape)
{
	t_mesh	*m;
	int		fd;

	if (!(m = mesh_create()))
		return (NULL);
	read_mesh_info(m, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) == -1)
		exit_message("Error loading model file!");
	read_mesh(fd, m, shape);
	close(fd);
	mesh_calc_bounds(m);
	return (m);
}
