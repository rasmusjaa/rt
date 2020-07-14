/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:31:38 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/13 18:41:00 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"

t_vec3 calc_smooth_normal(t_triface *tf, t_vec3 p)
{
	t_vec3 n;

	double p0 = ft_len_vec3(ft_sub_vec3(p, tf->v[0]));
	double p1 = ft_len_vec3(ft_sub_vec3(p, tf->v[1]));
	double p2 = ft_len_vec3(ft_sub_vec3(p, tf->v[2]));

	n = ft_add_vec3(ft_mul_vec3(tf->n[0], p0), ft_add_vec3(ft_mul_vec3(tf->n[1], p1), ft_mul_vec3(tf->n[2], p2)));
	return (ft_normalize_vec3(n));
}

int intersects_octree_model(t_ray *ray, t_shape *model, t_octree *node, t_raycast_hit *hit, int debug)
{
	size_t i;
	t_raycast_hit cur_hit;
	double min_dist;
	int hit_found;

	if (!intersects_bounds(ray, &(node->bounds), debug))
		return (FALSE);

	t_raycast_hit temp_hit;
	temp_hit.distance = MAX_CLIP;

	hit_found = FALSE;
	if (!node->is_last)
	{
		i = 0;
		while (i < NUM_CHILDREN)
		{
			if (intersects_octree_model(ray, model, node->children[i], &cur_hit, debug) && cur_hit.distance < temp_hit.distance)
			{
				temp_hit = cur_hit;
				*hit = temp_hit;
				hit_found = TRUE;
			}
			i++;
		}
	}
	else
	{
		if (debug)
			ft_printf("last\n");
		min_dist = MAX_CLIP;
		i = 0;
		while (i < node->num_tris)
		{
			if (intersects_triangle(ray, &(node->contains_trifaces[i]), &cur_hit))
			{
				if (debug)
					ft_printf("found triangle\n");
				hit_found = TRUE;
				if (cur_hit.distance < min_dist)
				{
					min_dist = cur_hit.distance;
					cur_hit.shape = model;
					*hit = cur_hit;
					hit->normal = cur_hit.normal;
				}
			}
			i++;
		}
	}
	return (hit_found);
}

int intersects_model(t_ray *ray, t_shape *model, t_raycast_hit *hit, int debug)
{
	size_t i;
	t_raycast_hit cur_hit;
	double min_dist;
	int hit_found;

	if (!intersects_bounds(ray, &(model->mesh->bounds), debug))
		return (FALSE);
	// else
	// {
	// 	hit->shape = model;
	// 	return (TRUE);
	// }

	hit_found = FALSE;
	min_dist = MAX_CLIP;
	i = 0;
	while (i < model->mesh->num_trifaces)
	{
		if (intersects_triangle(ray, &(model->mesh->trifaces[i]), &cur_hit))
		{
			hit_found = TRUE;
			if (cur_hit.distance < min_dist)
			{
				min_dist = cur_hit.distance;
				*hit = cur_hit;
				hit->shape = model;
			}
		}
		i++;
	}
	return (hit_found);
}
