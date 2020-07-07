/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:05:05 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/07 17:34:15 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "ft_get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

/*
** reads through the file as we need to know the count before reading for real
*/
static void read_mesh_info(t_mesh *m, const char *filename)
{
	int fd;
	char *line;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_putendl("Error loading file!");
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

/*
** vertex/uv/normal
** f 202/1/1 199/2/1 200/3/1
*/

static void parse_face(t_mesh *m, size_t i, char *line)
{
	size_t j;
	char **parts;
	char **tf;

	parts = ft_strsplit(line + 1, ' ');
	j = 0;
	while (parts[j])
	{
		tf = ft_strsplit(parts[j], '/');
		m->trifaces[i].v[j] = m->vertices[ft_atoi(tf[0]) - 1];
		m->trifaces[i].uv[j] = m->uvs[ft_atoi(tf[1]) - 1];
		m->trifaces[i].n[j] = m->normals[ft_atoi(tf[2]) - 1];
		free(tf[0]);
		free(tf[1]);
		free(tf[2]);
		free(tf);
		j++;
	}
	j = 0;
	while (parts[j])
		free(parts[j++]);
	free(parts);
	m->trifaces[i].e[0] = ft_sub_vec3(m->trifaces[i].v[1], m->trifaces[i].v[0]);
	m->trifaces[i].e[1] = ft_sub_vec3(m->trifaces[i].v[2], m->trifaces[i].v[1]);
	m->trifaces[i].e[2] = ft_sub_vec3(m->trifaces[i].v[0], m->trifaces[i].v[2]);
	m->trifaces[i].normal = /*ft_normalize_vec3(ft_cross_vec3(m->trifaces[i].e[0], ft_sub_vec3(m->trifaces[i].v[2], m->trifaces[i].v[0]))); */m->trifaces[i].n[0]; // this should not be here
}

t_mesh	*obj_load(const char *filename)
{
	t_mesh *m;
	int fd;
	char *line;
	size_t vi;
	size_t ni;
	size_t uvi;
	size_t ti;

	if (!(m = mesh_create()))
		return (NULL);
	read_mesh_info(m, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_putendl("Error loading file!");
	line = NULL;
	vi = 0;
	ni = 0;
	uvi = 0;
	ti = 0;
	while (ft_get_next_line(fd, &line))
	{
		if (ft_strncmp(line, "v ", 2) == 0)
		{
			m->vertices[vi] = ft_parse_vec3(line + 1);
			vi++;
		}
		else if (ft_strncmp(line, "vt", 2) == 0)
		{
			m->uvs[uvi] = ft_parse_vec2(line + 1);
			uvi++;
		}
		else if (ft_strncmp(line, "vn", 2) == 0)
		{
			m->normals[ni] = ft_parse_vec3(line + 2);
			ni++;
		}
		else if (ft_strncmp(line, "f ", 2) == 0)
		{
			parse_face(m, ti, line);
			ti++;
		}
		free(line);
	}
	close(fd);
	mesh_calc_bounds(m);
	return (m);
}