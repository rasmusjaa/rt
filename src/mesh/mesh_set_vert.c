/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_set_vert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 18:23:08 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/22 18:33:32 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "ft_printf.h"

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
