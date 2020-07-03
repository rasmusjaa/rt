/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:00:35 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/03 17:19:45 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# include <stdlib.h>
# include "vector.h"
# include "color.h"

typedef struct	s_triface
{
	t_vec3		v[3];
	t_vec3		n[3];
	t_vec3		uv[3];
	t_vec3		v0;
	t_vec3		v1;
	t_vec3		v2;
	t_vec3		n0;
	t_vec3		n1;
	t_vec3		n2;
	t_vec2		uv0;
	t_vec2		uv1;
	t_vec2		uv2;
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
}				t_mesh;

t_mesh			*mesh_create(void);
void			mesh_create_verts(t_mesh *m, size_t num_vertices);
void			mesh_create_trifaces(t_mesh *m, size_t num_trifaces);
void			mesh_set_vert(t_mesh *m, size_t i, t_vec3 v);

#endif
