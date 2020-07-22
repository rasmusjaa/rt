/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_csv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:08:04 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/22 14:11:17 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "shape.h"
#include <math.h>
#include <time.h>
#include <sys/stat.h>


t_shape_name_type_map g_shape_name_type_map[SHAPE_TYPES] =
{
	{PLANE_STR, PLANE},
	{SPHERE_STR, SPHERE},
	{CYL_STR, CYLINDER},
	{CONE_STR, CONE},
	{DISC_STR, DISC},
	{MODEL_STR, MODEL}
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

void	check_scene_fields(t_scene *scene, char *line, int n)
{
	double		values[N_SCENE_VALUES];

	n = 0;
	get_fields(line, values, N_SCENE_VALUES);
	scene->scene_config.shadows = round(ft_clamp_d0(values[0], 0, 1));
	scene->scene_config.shading = round(ft_clamp_d0(values[1], 0, 1));
	scene->scene_config.specular = round(ft_clamp_d0(values[2], 0, 1));
	scene->scene_config.opacity = round(ft_clamp_d0(values[3], 0, 1));
	scene->scene_config.refraction = round(ft_clamp_d0(values[4], 0, 1));
	scene->scene_config.reflection = round(ft_clamp_d0(values[5], 0, 1));
	scene->scene_config.bounces = round(ft_clamp_d(values[6], MIN_BOUNCES, MAX_BOUNCES));
	scene->scene_config.width = round(ft_clamp_d(values[7], MIN_WIDTH, MAX_WIDTH));
	scene->scene_config.height = round(ft_clamp_d(values[8], MIN_HEIGHT, MAX_HEIGHT));
	scene->scene_config.ambient = ft_clamp_rgba(ft_make_rgba(values[10], values[10], values[11], values[12]));
}

void	check_camera_fields(t_scene *scene, char *line, int n)
{
	double		values[N_CAMERA_VALUES];

	get_fields(line, values, N_CAMERA_VALUES);
	scene->cameras[n].position = ft_clamp_vec3(ft_make_vec3(values[0], values[1], values[2]), MIN_COORD, MAX_COORD);
	scene->cameras[n].target = ft_clamp_vec3(ft_make_vec3(values[3], values[4], values[5]), MIN_COORD, MAX_COORD);
	scene->cameras[n].rotation = ft_clamp_vec3(ft_make_vec3(-values[6], -values[7], -values[8]), 0, 360);
	scene->cameras[n].fov = ft_clamp_d(values[9], MIN_FOV, MAX_FOV);
	scene->cameras[n].type = round(ft_clamp_d0(values[10], 0, CAMERA_TYPES - 1));
	scene->cameras[n].aspect = ft_clamp_d(values[11], MIN_ASPECT, MAX_ASPECT);
	scene->cameras[n].aspect = scene->cameras[n].aspect;
}

static t_shape_type	get_shape_type(char *line)
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

static char	*get_shape_name(t_shape_type type)
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


void	check_shape_fields(t_scene *scene, char *line, int n)
{
	double		values[N_SHAPE_VALUES];
	char		file[256];
	char		*file_pointer;
	t_shape		*shape;

	shape = &scene->shapes[n];
	get_fields(line, values, N_SHAPE_VALUES);
	shape->type = get_shape_type(line);
	shape->name = get_shape_name(shape->type); // eiks taa kannata yhdistaa ylempaan ku looppaa saman asian? tai alemmas kun on kaikki tyypit iffil
	shape->position = ft_clamp_vec3(ft_make_vec3(values[0], values[1], values[2]), MIN_COORD, MAX_COORD);
	shape->target = ft_clamp_vec3(ft_make_vec3(values[3], values[4], values[5]), MIN_COORD, MAX_COORD);
	shape->rotation = ft_clamp_vec3(ft_make_vec3(-values[6], -values[7], -values[8]), 0, 360);
	shape->scale = ft_clamp_d(values[9], MIN_SCALE, MAX_SCALE);
	shape->color = ft_clamp_rgba(ft_make_rgba(values[10], values[11], values[12], values[13]));
	shape->radius = shape->scale * ft_clamp_d(values[14], MIN_RADIUS, MAX_RADIUS);
	shape->angle = ft_clamp_d(values[15], MIN_ANGLE, MAX_ANGLE);
	shape->opacity = ft_clamp_d(values[16], 0, 1);
	shape->reflection = ft_clamp_d(values[17], 0, 1);
	shape->refraction = ft_clamp_d(values[18], 1, 5);
	shape->shine = ft_clamp_d(values[19], 0, 1);
	if (shape->type == MODEL)
	{
		file_pointer = get_shape_file(line, N_SHAPE_VALUES);
		if (file_pointer == NULL)
			exit_message("no model on model line");
		ft_strcpy(file, file_pointer);
		shape->mesh = obj_load(file, *shape);
		shape->octree = octree_create_node(shape->mesh->bounds, shape->mesh->num_trifaces, shape->mesh->trifaces);
		ft_printf("loaded model from file %s\n", file);
	}
	else
	{
		if (shape->position.x == shape->target.x && shape->position.y == shape->target.y && shape->position.z == shape->target.z)
			shape->target.y = shape->position.y + 1;
		shape->target = ft_normalize_vec3(ft_rotate_vec3(ft_sub_vec3(shape->target, shape->position), shape->rotation));
	}
}

void	check_light_fields(t_scene *scene, char *line, int n)
{
	double		values[N_LIGHT_VALUES];

	get_fields(line, values, N_LIGHT_VALUES);
	scene->lights[n].position = ft_clamp_vec3(ft_make_vec3(values[0], values[1], values[2]), MIN_COORD, MAX_COORD);
	scene->lights[n].color = ft_clamp_rgba(ft_make_rgba(values[3], values[4], values[5], 1.0));
	scene->lights[n].type = round(ft_clamp_d0(values[6], 0, LIGHT_TYPES - 1));
	scene->lights[n].intensity = ft_clamp_d(values[7], MIN_INTENSITY, MAX_INTENSITY);
	scene->lights[n].radius = ft_clamp_d(values[8], 0, 5);
	scene->lights[n].leds = round(ft_clamp_d(values[9], 2, 100));
}

void exit_message(char *error)
{
	ft_putendl_fd(error, 2);
	exit(1);
}

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
	{POINT_LIGHT_STR, check_light_fields, LIGHT}
};

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

int		init_scene(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	size_t	i;

	scene->help_ray = 0;
	scene->scene_config.colorize = 0;
	scene->num_all[0] = 0;
	scene->num_all[1] = 0;
	scene->num_all[2] = 0;
	scene->num_all[3] = 0;
	scene->scene_config.filepath = file;
	scene->scene_config.last_modified = last_modified(file);

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_message("Error loading file!");
	while (ft_get_next_line(fd, &line) > 0)
	{
		i = 0;
		while (i < N_UNIQUE_OBJS)
		{
			if (ft_strncmp(line, g_unique_objs[i].obj_str, ft_strlen(g_unique_objs[i].obj_str)) == 0) // hiukan raskas kun kattoo joka rivilla kaikkien pituuden uusiks
			{
				scene->num_all[g_unique_objs[i].type]++;
			}
			i++;
		}
		free(line);
	}
	close(fd);
	scene->num_cameras = scene->num_all[CAMERA];
	scene->cur_camera = 0;
	scene->num_shapes = scene->num_all[SHAPE];
	scene->num_lights = scene->num_all[LIGHT];
	if (!(scene->cameras = (t_camera*)malloc(sizeof(t_camera) * scene->num_cameras)) ||
	!(scene->shapes = (t_shape*)malloc(sizeof(t_shape) * scene->num_shapes)) ||
	!(scene->lights = (t_light*)malloc(sizeof(t_light) * scene->num_lights)))
		return (0);
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
