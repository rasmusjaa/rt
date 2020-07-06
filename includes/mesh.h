/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:00:35 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/06 13:25:55 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# include <stdlib.h>
# include "vector.h"
# include "color.h"

# define MAX_BOUNDS 10000
# define MIN_BOUNDS -10000

typedef struct	s_bounds
{
	t_vec3		min;
	t_vec3		max;
}				t_bounds;

typedef struct	s_triface
{
	t_vec3		v[3];
	t_vec3		n[3];
	t_vec2		uv[3];
	t_vec3		normal;
	t_vec3		e[3];
}				t_triface;

typedef struct	s_mesh
{
	t_triface	*trifaces;
	size_t		num_trifaces;
	t_vec3		*vertices;
	size_t		num_vertices;
	t_vec3		*normals;
	size_t		num_normals;
	t_vec2		*uvs;
	size_t		num_uvs;
	t_bounds	bounds;
}				t_mesh;

t_mesh			*mesh_create(void);
void			mesh_destroy(t_mesh *m);
void			mesh_create_verts(t_mesh *m, size_t num_vertices);
void			mesh_create_normals(t_mesh *m, size_t num_normals);
void			mesh_create_uvs(t_mesh *m, size_t num_uvs);
void			mesh_create_trifaces(t_mesh *m, size_t num_trifaces);
void			mesh_set_vert(t_mesh *m, size_t i, t_vec3 v);
void			mesh_calc_bounds(t_mesh *m);

#endif
