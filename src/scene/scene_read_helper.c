/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_read_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 14:56:18 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 15:33:35 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "bounds.h"
#include "vector.h"
#include <sys/stat.h>
#include <time.h>
#include "shape.h"
#include "material.h"
#include "object.h"
#include "libft.h"
#include "ft_printf.h"

t_shape_type	get_shape_type(char *line)
{
	int i;

	i = 0;
	while (i < SHAPE_TYPES)
	{
		if (ft_strncmp(line, g_shape_name_type_map[i].name, 4) == 0)
			return ( g_shape_name_type_map[i].type);
		i++;
	}
	ft_printf("Error reading shape from: %s\n", line);
	return (-1);
}

char	*get_shape_name(t_shape_type type)
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

time_t	last_modified(char *file)
{
	struct stat		buf;
	time_t modified;

	modified = 0;
	if (lstat(file, &buf) != -1 && S_ISDIR(buf.st_mode) == 0)
		modified = buf.st_mtime;
	else
		exit_message("Failed to get scene file stats, check file rights");
	return (modified);
}

char	*get_shape_file(char *line, int num_values)
{
	int i;
	int field;

	i = 0;
	field = -1;
	while (line[i])
	{
		if (line[i] == ';')
		{
			field++;
			if (field == num_values && line[i + 1])
			{
				return (&line[i + 1]);
			}
		}
		i++;
	}
	return (NULL);
}

t_bounds	make_shape_bounds(t_vec3 pos, double *values)
{
	t_bounds	b;

	b.active = FALSE;
	b.min.x = -MAX_CLIP;
	b.max.x = MAX_CLIP;
	b.min.y = -MAX_CLIP;
	b.max.y = MAX_CLIP;
	b.min.z = -MAX_CLIP;
	b.max.z = MAX_CLIP;
	if (ft_abs_d(values[14] - values[17]) > EPSILON)
	{
		b.min.x = pos.x + values[14];
		b.max.x = pos.x + values[17];
		b.active = TRUE;
	}
	if (ft_abs_d(values[15] - values[18]) > EPSILON)
	{
		b.min.y = pos.y + values[15];
		b.max.y = pos.y + values[18];
		b.active = TRUE;
	}
	if (ft_abs_d(values[16] - values[19]) > EPSILON)
	{
		b.min.z = pos.z + values[16];
		b.max.z = pos.z + values[19];
		b.active = TRUE;
	}
	return (b);
}

void	link_shapes_materials_textures(t_scene *scene)
{
	size_t		i;

	i = 0;
	while (i < scene->num_materials)
	{
		scene->materials[i].texture = get_texture_by_id(scene, scene->materials[i].texture_id);
		i++;
	}
	i = 0;
	while (i < scene->num_shapes)
	{
		scene->shapes[i].material = get_material_by_id(scene, scene->shapes[i].material_id);
		if (scene->shapes[i].material == NULL)
		{
			scene->shapes[i].material = (t_material*)malloc(sizeof(t_material));
			*(scene->shapes[i].material) = new_material(DEFAULT_MATERIAL_ID, scene->shapes[i].color, NULL);
		}
		i++;
	}
}
