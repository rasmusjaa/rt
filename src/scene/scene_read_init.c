/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_read_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 14:35:34 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 14:19:59 by wkorande         ###   ########.fr       */
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

static void		allocate_mem(t_scene *scn)
{
	scn->cur_camera = 0;
	scn->num_settings = scn->num_all[SETTINGS];
	scn->num_cameras = scn->num_all[CAMERA];
	scn->num_shapes = scn->num_all[SHAPE];
	scn->num_lights = scn->num_all[LIGHT];
	scn->num_materials = scn->num_all[MATERIAL];
	scn->num_textures = scn->num_all[TEXTURE];
	if (!(scn->cameras =
		(t_camera*)malloc(sizeof(t_camera) * scn->num_cameras)) ||
		!(scn->shapes = (t_shape*)malloc(sizeof(t_shape) * scn->num_shapes)) ||
		!(scn->lights = (t_light*)malloc(sizeof(t_light) * scn->num_lights)) ||
		!(scn->textures =
			(t_texture*)malloc(sizeof(t_texture) * scn->num_textures)) ||
		!(scn->materials =
			(t_material*)malloc(sizeof(t_material) * scn->num_materials)))
		exit_message("Error allocating scene contents");
	scn->cube_map = NULL;
}

static	void	pre_init_scene(t_scene *scene, char *file)
{
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
}

int				init_scene(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	size_t	i;

	pre_init_scene(scene, file);
	fd = open(file, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) == -1)
		exit_message("Error loading file!");
	while (ft_get_next_line(fd, &line) > 0)
	{
		i = 0;
		while (i < N_UNIQUE_OBJS)
		{
			if (ft_strncmp(line, g_unique_objs[i].obj_str,
				ft_strlen(g_unique_objs[i].obj_str)) == 0)
				scene->num_all[g_unique_objs[i].type]++;
			i++;
		}
		free(line);
	}
	close(fd);
	allocate_mem(scene);
	return (1);
}
