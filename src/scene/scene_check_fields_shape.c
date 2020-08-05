/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check_fields_shape.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 13:20:07 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 14:28:49 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "scene.h"
#include "libft.h"
#include "obj_loader.h"
#include "ft_printf.h"
#include "object.h"

static t_shape_type	get_shape_type(char *line)
{
	int i;

	i = 0;
	while (i < SHAPE_TYPES)
	{
		if (ft_strncmp(line, g_shape_name_type_map[i].name, 4) == 0)
			return (g_shape_name_type_map[i].type);
		i++;
	}
	ft_printf("Error reading shape from: %s\n", line);
	return (-1);
}

static char			*get_shape_name(t_shape_type type)
{
	int i;

	i = 0;
	while (i < SHAPE_TYPES)
	{
		if (g_shape_name_type_map[i].type == type)
			return (g_shape_name_type_map[i].name);
		i++;
	}
	return (SHAPE_ERROR_STR);
}

static void			handle_model(t_shape *s, char *line)
{
	char		file[256];
	char		*file_pointer;
	int			i;

	file_pointer = get_shape_file(line, N_SHAPE_VALUES);
	if (file_pointer == NULL)
		exit_message("no model on model line");
	i = 0;
	while (file_pointer[0 + i] != '\n' && file_pointer[0 + i] != ';' &&
		file_pointer[0 + i] != 0)
		i++;
	ft_strncpy(file, file_pointer, i);
	file[i] = 0;
	s->mesh = obj_load(file, *s);
	s->octree = octree_create_node(s->mesh->bounds, s->mesh->num_trifaces,
		s->mesh->trifaces);
	ft_printf("loaded model from file %s\n", file);
}

void				check_shape_fields(t_scene *scene, char *line, int n)
{
	double	vals[N_SHAPE_VALUES];
	t_shape *s;

	s = &scene->shapes[n];
	get_fields(line, vals, N_SHAPE_VALUES);
	s->type = get_shape_type(line);
	s->name = get_shape_name(s->type);
	s->position = ft_clamp_vec3(ft_make_vec3(vals[0], vals[1], vals[2]),
		MIN_COORD, MAX_COORD);
	s->target = ft_add_vec3(s->position, ft_make_vec3(0, 1, 0));
	s->rotation = ft_clamp_vec3(ft_make_vec3(-vals[3], -vals[4],
		-vals[5]), 0, 360);
	s->scale = ft_clamp_d(vals[6], MIN_SCALE, MAX_SCALE);
	s->color = ft_clamp_rgba(ft_make_rgba(vals[7], vals[8], vals[9], vals[10]));
	s->radius = s->scale * ft_clamp_d(vals[11], MIN_RADIUS, MAX_RADIUS);
	s->angle = ft_clamp_d(vals[12], MIN_ANGLE, MAX_ANGLE);
	s->material_id = (int)vals[13];
	s->bounds = make_shape_bounds(s->position, vals);
	if (s->type == MODEL)
		handle_model(s, line);
	else
		s->target = ft_normalize_vec3(ft_rotate_vec3(ft_sub_vec3(s->target,
			s->position), s->rotation));
}
