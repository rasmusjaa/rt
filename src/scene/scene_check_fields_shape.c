/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check_fields_shape.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 13:20:07 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 13:24:10 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "scene.h"
#include "libft.h"
#include "obj_loader.h"
#include "ft_printf.h"

void	check_shape_fields(t_scene *scene, char *line, int n)
{
	double		values[N_SHAPE_VALUES];
	char		file[256];
	char		*file_pointer;
	t_shape		*s;
	int			i;

	s = &scene->shapes[n];
	get_fields(line, values, N_SHAPE_VALUES);
	s->type = get_shape_type(line);
	s->name = get_shape_name(s->type);
	s->position = ft_clamp_vec3(ft_make_vec3(values[0], values[1], values[2]), MIN_COORD, MAX_COORD);
	s->target = ft_add_vec3(s->position, ft_make_vec3(0, 1, 0));
	s->rotation = ft_clamp_vec3(ft_make_vec3(-values[3], -values[4], -values[5]), 0, 360);
	s->scale = ft_clamp_d(values[6], MIN_SCALE, MAX_SCALE);
	s->color = ft_clamp_rgba(ft_make_rgba(values[7], values[8], values[9], values[10]));
	s->radius = s->scale * ft_clamp_d(values[11], MIN_RADIUS, MAX_RADIUS);
	s->angle = ft_clamp_d(values[12], MIN_ANGLE, MAX_ANGLE);
	s->material_id = (int)values[13];
	s->bounds = make_shape_bounds(s->position, values);
	if (s->type == MODEL)
	{
		file_pointer = get_shape_file(line, N_SHAPE_VALUES);
		if (file_pointer == NULL)
			exit_message("no model on model line");
		i = 0;
		while(file_pointer[0 + i] != '\n' && file_pointer[0 + i] != ';' && file_pointer[0 + i] != 0)
			i++;
		ft_strncpy(file, file_pointer, i);
		file[i] = 0;
		s->mesh = obj_load(file, *s);
		s->octree = octree_create_node(s->mesh->bounds, s->mesh->num_trifaces, s->mesh->trifaces);
		ft_printf("loaded model from file %s\n", file);
	}
	else
		s->target = ft_normalize_vec3(ft_rotate_vec3(ft_sub_vec3(s->target, s->position), s->rotation));
}
