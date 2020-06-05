/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_csv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:08:04 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/05 16:17:38 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_fields(char *line, double *values)
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
			if (field <= N_VALUES)
			{
				values[field] = ft_strod(line[i + 1]);
			}
		}
		i++;
	}
}

t_vec3	clamp_vec_3(t_vec3 v, double min, double max)
{
	ft_clamp_d(v.x, min, max);
	ft_clamp_d(v.y, min, max);
	ft_clamp_d(v.z, min, max);
	return (v);
}

void	check_scene_fields(char *line, int n)
{
	double		values[N_SCENE_VALUES];
	size_t		i;

	i = 0;
	get_fields(line, values);
	rt->scenes[0]->position = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), MIN_COORD, MAX_COORD);
	rt->scenes[0]->target = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), MIN_COORD, MAX_COORD);
	rt->scenes[0]->rotation = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), 0, 360);
	rt->scenes[0]->scale = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), MIN_SCALE, MAX_SCALE);
	rt->scenes[0]->color = ft_clamp_rgba(ft_make_rgba(values[i++], values[i++], values[i++], values[i++]));
	rt->scenes[0]->radius = ft_clamp_d(values[i++], MIN_RADIUS, MAX_RADIUS);
	rt->scenes[0]->angle = ft_clamp_d(values[i++], MIN_ANGLE, MAX_ANGLE);
	rt->scenes[0]->opacity = ft_clamp_d(values[i++], 0, 1);
}

void	check_camera_fields(char *line, t_scene *scene, int n)
{
	double		values[N_CAMERA_VALUES];
	size_t		i;

	i = 0;
	get_fields(line, values);
	scene->cameras[n]->position = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), MIN_COORD, MAX_COORD);
	scene->cameras[n]->target = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), MIN_COORD, MAX_COORD);
	scene->cameras[n]->rotation = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), 0, 360);
	scene->cameras[n]->scale = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), MIN_SCALE, MAX_SCALE);
	scene->cameras[n]->color = ft_clamp_rgba(ft_make_rgba(values[i++], values[i++], values[i++], values[i++]));
	scene->cameras[n]->radius = ft_clamp_d(values[i++], MIN_RADIUS, MAX_RADIUS);
	scene->cameras[n]->angle = ft_clamp_d(values[i++], MIN_ANGLE, MAX_ANGLE);
	scene->cameras[n]->opacity = ft_clamp_d(values[i++], 0, 1);
}

void	check_shape_fields(char *line, int n)
{
	double		values[N_SHAPE_VALUES];
	size_t		i;

	i = 0;
	get_fields(line, values);
	rt->objects[n]->position = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), MIN_COORD, MAX_COORD);
	rt->objects[n]->target = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), MIN_COORD, MAX_COORD);
	rt->objects[n]->rotation = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), 0, 360);
	rt->objects[n]->scale = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), MIN_SCALE, MAX_SCALE);
	rt->objects[n]->color = ft_clamp_rgba(ft_make_rgba(values[i++], values[i++], values[i++], values[i++]));
	rt->objects[n]->radius = ft_clamp_d(values[i++], MIN_RADIUS, MAX_RADIUS);
	rt->objects[n]->angle = ft_clamp_d(values[i++], MIN_ANGLE, MAX_ANGLE);
	rt->objects[n]->opacity = ft_clamp_d(values[i++], 0, 1);
}

void	check_light_fields(char *line, int n)
{
	double		values[N_LIGHT_VALUES];
	size_t		i;

	i = 0;
	get_fields(line, values);
	rt->objects[n]->position = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), MIN_COORD, MAX_COORD);
	rt->objects[n]->target = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), MIN_COORD, MAX_COORD);
	rt->objects[n]->rotation = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), 0, 360);
	rt->objects[n]->scale = ft_clamp_vec3(ft_make_vec3(values[i++], values[i++], values[i++]), MIN_SCALE, MAX_SCALE);
	rt->objects[n]->color = ft_clamp_rgba(ft_make_rgba(values[i++], values[i++], values[i++], values[i++]));
	rt->objects[n]->radius = ft_clamp_d(values[i++], MIN_RADIUS, MAX_RADIUS);
	rt->objects[n]->angle = ft_clamp_d(values[i++], MIN_ANGLE, MAX_ANGLE);
	rt->objects[n]->opacity = ft_clamp_d(values[i++], 0, 1);
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
	ft_putendl(str);
	exit(1);
}

int			handle_line(char *str)
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
			g_objects[i].func(str, object_num[g_objects[i].type]);
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
	return (1);
}

t_scene		*read_scene(char *file, t_rt *rt)
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
		handle_line(line);
		free(line);
	}
	close(fd);
	return (scene);
}
