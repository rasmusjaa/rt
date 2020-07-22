/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 18:23:33 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/22 18:23:48 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

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
