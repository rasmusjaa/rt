/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_calc_bounds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 18:22:34 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/22 18:26:52 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

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
