/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_csv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:08:04 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/06 09:45:21 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

void	get_fields(char *line, double *values, int num_values)
{
	int i;
	int field;

	i = 0;
	field = 0;
	while (line[i])
	{
		if (line[i] == ';')
		{
			field++;
			if (field <= num_values)
			{
				values[field] = ft_strtod(&line[i + 1]);
			}
		}
		i++;
	}
}

t_vec3	ft_clamp_vec3(t_vec3 v, double min, double max)
{
	ft_clamp_d(v.x, min, max);
	ft_clamp_d(v.y, min, max);
	ft_clamp_d(v.z, min, max);
	return (v);
}

void	check_scene_fields(t_scene *scene, char *line, int n)
{
	double		values[N_SCENE_VALUES];

	n = 0;
	get_fields(line, values, N_SCENE_VALUES);
	scene->scene_config.shadows = round(ft_clamp_d0(values[0], 0, 1));
	scene->scene_config.shading = round(ft_clamp_d0(values[1], 0, 1));
	scene->scene_config.speculars = round(ft_clamp_d0(values[2], 0, 1));
	scene->scene_config.refraction = round(ft_clamp_d0(values[3], 0, 1));
	scene->scene_config.reflection = round(ft_clamp_d0(values[4], 0, 1));
	scene->scene_config.bounces = round(ft_clamp_d0(values[5], 0, 1));
}

void	check_camera_fields(t_scene *scene, char *line, int n)
{
	double		values[N_CAMERA_VALUES];

	get_fields(line, values, N_CAMERA_VALUES);
	// camera type missing
	scene->cameras[n].position = ft_clamp_vec3(ft_make_vec3(values[0], values[1], values[2]), MIN_COORD, MAX_COORD);
	scene->cameras[n].target = ft_clamp_vec3(ft_make_vec3(values[3], values[4], values[5]), MIN_COORD, MAX_COORD);
	scene->cameras[n].rotation = ft_clamp_vec3(ft_make_vec3(values[6], values[7], values[8]), 0, 360);
	scene->cameras[n].fov = ft_clamp_d0(values[9], MIN_FOV, MAX_FOV);
	scene->cameras[n].type = round(ft_clamp_d0(values[10], 0, CAMERA_TYPES - 1));
	scene->cameras[n].aspect = ft_clamp_d0(values[11], MIN_ASPECT, MAX_ASPECT);
	scene->cameras[n].width = round(ft_clamp_d0(values[12], MIN_WIDTH, MAX_WIDTH));
	scene->cameras[n].height = round(ft_clamp_d0(values[13], MIN_HEIGHT, MAX_HEIGHT));

}

void	check_shape_fields(t_scene *scene, char *line, int n)
{
	double		values[N_SHAPE_VALUES];
	size_t		i;

	i = 0;
	get_fields(line, values, N_SHAPE_VALUES);
	// shape type missing
	scene->shapes[n].position = ft_clamp_vec3(ft_make_vec3(values[0], values[1], values[2]), MIN_COORD, MAX_COORD);
	scene->shapes[n].target = ft_clamp_vec3(ft_make_vec3(values[3], values[4], values[5]), MIN_COORD, MAX_COORD);
	scene->shapes[n].rotation = ft_clamp_vec3(ft_make_vec3(values[6], values[7], values[8]), 0, 360);
	scene->shapes[n].scale = ft_clamp_vec3(ft_make_vec3(values[9], values[10], values[11]), MIN_SCALE, MAX_SCALE);
	scene->shapes[n].color = ft_clamp_rgba(ft_make_rgba(values[12], values[13], values[14], values[i]));
	scene->shapes[n].radius = ft_clamp_d(values[15], MIN_RADIUS, MAX_RADIUS);
	scene->shapes[n].angle = ft_clamp_d(values[16], MIN_ANGLE, MAX_ANGLE);
	scene->shapes[n].opacity = ft_clamp_d(values[17], 0, 1);
}

void	check_light_fields(t_scene *scene, char *line, int n)
{
	double		values[N_LIGHT_VALUES];
	
	get_fields(line, values, N_LIGHT_VALUES);
	// light type missing
	scene->lights[n].position = ft_clamp_vec3(ft_make_vec3(values[0], values[1], values[2]), MIN_COORD, MAX_COORD);
	scene->lights[n].color = ft_clamp_rgba(ft_make_rgba(values[3], values[4], values[5], 1.0));
	scene->lights[n].type = round(ft_clamp_d0(values[6], 0, LIGHT_TYPES - 1));
	scene->lights[n].intensity = ft_clamp_d(values[7], MIN_INTENSITY, MAX_INTENSITY);
}

t_objects g_objects[N_OBJECTS] =
{
	{"scen", check_scene_fields, SCENE},
	{"came", check_camera_fields, CAMERA},
	{"sphe", check_shape_fields, SHAPE},
	{"plan", check_shape_fields, SHAPE},
	{"cyli", check_shape_fields, SHAPE},
	{"cone", check_shape_fields, SHAPE},
	{"spot", check_light_fields, LIGHT}
};

void exit_message(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

int			handle_line(t_scene *scene, char *str)
{
	int i;
	int	object_num[4];

	i = 0;
	object_num[0] = 0;
	object_num[1] = 0;
	object_num[2] = 0;
	object_num[3] = 0;
	while (i < N_OBJECTS)
	{
		if (ft_strncmp(str, g_objects[i].object, 4) == 0)
		{
			g_objects[i].func(scene, str, object_num[g_objects[i].type]);
			object_num[g_objects[i].type]++;
		}
		i++;
	}
	i = 0;
	return (0);
}

int		init_scene(char *str, t_scene *scene)
{
	int		fd;
	char	*line;
	int		i;
	
	scene->num_all[0] = 0;
	scene->num_all[1] = 0;
	scene->num_all[2] = 0;
	scene->num_all[3] = 0;
	// init_scenes();
	// init_cameras();
	// init_shapes();

	fd = open(str, O_RDONLY);
	if (fd < 0)
		exit_message("Invalid file");
	while (ft_get_next_line(fd, &line) > 0)
	{
		i = 0;
		while (i < N_OBJECTS)
		{
			if (ft_strncmp(str, g_objects[i].object, 4) == 0)
			{
				scene->num_all[g_objects[i].type]++;
				scene->num_objects++;
			}
			i++;
		}
		free(line);
	}
	close(fd);
	// scene->num_scenes = scene->num_all[SCENE];
	scene->num_cameras = scene->num_all[CAMERA];
	scene->num_shapes = scene->num_all[SHAPE];
	scene->num_lights = scene->num_all[LIGHT];
	// need to allocate memory for all object types
	return (1);
}

t_scene		*read_scene(char *file)
{
	int		fd;
	char	*line;
	t_scene *scene;

	if (!(scene = (t_scene*)malloc(sizeof(t_scene))))
		exit_message("Failed to malloc scene!");
	if (!init_scene(file, scene))
		exit_message("Failed to init scene!");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_message("Invalid file");
	while (ft_get_next_line(fd, &line) > 0)
	{
		handle_line(scene, line);
		free(line);
	}
	close(fd);
	return (scene);
}
