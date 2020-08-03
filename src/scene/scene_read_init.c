/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_read_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 14:35:34 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 15:32:27 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "scene.h"
#include "object.h"
#include "shape.h"
#include "texture.h"
#include <unistd.h>
#include "libft.h"
#include "ft_get_next_line.h"

int		init_scene(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	size_t	i;

	scene->help_ray = 0;
	scene->scene_config.colorize = 0;
	scene->num_all[SETTINGS] = 0;
	scene->num_all[CAMERA] = 0;
	scene->num_all[SHAPE] = 0;
	scene->num_all[LIGHT] = 0;
	scene->num_all[MATERIAL] = 0;
	scene->num_all[TEXTURE] = 0;
	scene->scene_config.filepath = file;
	scene->scene_config.last_modified = last_modified(file);
	fd = open(file, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) == -1)
		exit_message("Error loading file!");
	while (ft_get_next_line(fd, &line) > 0)
	{
		i = 0;
		while (i < N_UNIQUE_OBJS)
		{
			if (ft_strncmp(line, g_unique_objs[i].obj_str, ft_strlen(g_unique_objs[i].obj_str)) == 0) // hiukan raskas kun kattoo joka rivilla kaikkien pituuden uusiks
				scene->num_all[g_unique_objs[i].type]++;
			i++;
		}
		free(line);
	}
	close(fd);
	scene->cur_camera = 0;
	scene->num_settings = scene->num_all[SETTINGS];
	scene->num_cameras = scene->num_all[CAMERA];
	scene->num_shapes = scene->num_all[SHAPE];
	scene->num_lights = scene->num_all[LIGHT];
	scene->num_materials = scene->num_all[MATERIAL];
	scene->num_textures = scene->num_all[TEXTURE];
	if (!(scene->cameras = (t_camera*)malloc(sizeof(t_camera) * scene->num_cameras)) ||
		!(scene->shapes = (t_shape*)malloc(sizeof(t_shape) * scene->num_shapes)) ||
		!(scene->lights = (t_light*)malloc(sizeof(t_light) * scene->num_lights)) ||
		!(scene->textures = (t_texture*)malloc(sizeof(t_texture) * scene->num_textures)) ||
		!(scene->materials = (t_material*)malloc(sizeof(t_material) * scene->num_materials))
	)
		exit_message("Error allocating scene contents");
	scene->cube_map = NULL;
	return (1);
}
