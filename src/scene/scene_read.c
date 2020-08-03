/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 18:05:01 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 15:40:38 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt.h"
#include "ft_printf.h"
#include "texture.h"
#include "material.h"
#include "shape.h"
#include <unistd.h>
#include "ft_get_next_line.h"
#include "object.h"

t_shape_name_type_map g_shape_name_type_map[SHAPE_TYPES] =
{
	{PLANE_STR, PLANE},
	{SPHERE_STR, SPHERE},
	{CYL_STR, CYLINDER},
	{CONE_STR, CONE},
	{DISC_STR, DISC},
	{MODEL_STR, MODEL},
};

t_unique_obj g_unique_objs[N_UNIQUE_OBJS] =
{
	{SETTINGS_STR, check_scene_fields, SETTINGS},
	{CAMERA_STR, check_camera_fields, CAMERA},
	{SPHERE_STR, check_shape_fields, SHAPE},
	{PLANE_STR, check_shape_fields, SHAPE},
	{CYL_STR, check_shape_fields, SHAPE},
	{CONE_STR, check_shape_fields, SHAPE},
	{DISC_STR, check_shape_fields, SHAPE},
	{MODEL_STR, check_shape_fields, SHAPE},
	{POINT_LIGHT_STR, check_light_fields, LIGHT},
	{MATERIAL_STR, check_material_fields, MATERIAL},
	{TEXTURE_STR, check_texture_fields, TEXTURE}
};

void	get_fields(char *line, double *values, int num_values)
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
			if (field < num_values)
			{
				values[field] = ft_strtod(&line[i + 1]);
			}
		}
		i++;
	}
}

int			handle_line(t_scene *scene, char *line)
{
	int i;
	int n;

	i = 0;
	while (i < N_UNIQUE_OBJS)
	{
		if (ft_strncmp(line, g_unique_objs[i].obj_str, ft_strlen(g_unique_objs[i].obj_str)) == 0) // sama kun alemmassa
		{
			scene->num_all[g_unique_objs[i].type]--;
			n = scene->num_all[(int)g_unique_objs[i].type];
			g_unique_objs[i].func(scene, line, n);
		}
		i++;
	}
	return (0);
}

void	reload_scene(t_rt *rt)
{
	t_scene *scene;
	char	*file;
	int		width;
	int		height;

	scene = rt->scenes[rt->cur_scene];
	file = scene->scene_config.filepath;
	width = scene->scene_config.width;
	height = scene->scene_config.height;
	ft_printf("old width %d height %d\n", width, height);
	destroy_scene(rt, scene);
	rt->scenes[rt->cur_scene] = read_scene(rt, file);
	rt->scenes[rt->cur_scene]->scene_config.width = width;
	rt->scenes[rt->cur_scene]->scene_config.height = height;
	ft_printf("old width %d height %d\n", rt->scenes[rt->cur_scene]->scene_config.width, rt->scenes[rt->cur_scene]->scene_config.height);
	rt->render_requested = TRUE;
}

t_scene		*read_scene(t_rt *rt, char *file)
{
	int		fd;
	char	*line;
	t_scene *scene;

	line = NULL;
	if (!(scene = (t_scene*)malloc(sizeof(t_scene))))
		exit_message("Failed to malloc scene!");
	if (!init_scene(file, scene))
		exit_message("Failed to init scene!");
	scene->rt = rt;
	fd = open(file, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) == -1)
		exit_message("Invalid file");
	while (ft_get_next_line(fd, &line) > 0)
	{
		handle_line(scene, line);
		free(line);
	}
	close(fd);
	if (scene->num_settings < 1 || scene->num_cameras < 1)
		exit_message("No settings or camera in scene file");
	link_shapes_materials_textures(scene);
	scene->cube_map = get_texture_by_id(scene, scene->scene_config.sky_tex_id);
	if (!scene->cube_map || scene->cube_map->procedural_type || !scene->cube_map->img_data)
		scene->cube_map = NULL;
	return (scene);
}
