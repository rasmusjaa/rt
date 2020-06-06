/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_csv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:08:04 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/06 14:41:20 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

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
	scene->scene_config.specular = round(ft_clamp_d0(values[2], 0, 1));
	scene->scene_config.refraction = round(ft_clamp_d0(values[3], 0, 1));
	scene->scene_config.reflection = round(ft_clamp_d0(values[4], 0, 1));
	scene->scene_config.bounces = round(ft_clamp_d0(values[5], MIN_BOUNCES, MAX_BOUNCES));
}

void	check_camera_fields(t_scene *scene, char *line, int n)
{
	double		values[N_CAMERA_VALUES];

	get_fields(line, values, N_CAMERA_VALUES);
	scene->cameras[n].position = ft_clamp_vec3(ft_make_vec3(values[0], values[1], values[2]), MIN_COORD, MAX_COORD);
	scene->cameras[n].target = ft_clamp_vec3(ft_make_vec3(values[3], values[4], values[5]), MIN_COORD, MAX_COORD);
	scene->cameras[n].rotation = ft_clamp_vec3(ft_make_vec3(values[6], values[7], values[8]), 0, 360);
	scene->cameras[n].fov = ft_clamp_d0(values[9], MIN_FOV, MAX_FOV);
	scene->cameras[n].type = round(ft_clamp_d0(values[10], 0, CAMERA_TYPES - 1));
	scene->cameras[n].aspect = ft_clamp_d0(values[11], MIN_ASPECT, MAX_ASPECT);
	scene->cameras[n].width = round(ft_clamp_d0(values[12], MIN_WIDTH, MAX_WIDTH));
	scene->cameras[n].height = round(ft_clamp_d0(values[13], MIN_HEIGHT, MAX_HEIGHT));

}

static t_shape_type	get_shape_type(char *line)
{
	if (ft_strncmp(line, "sphe", 4) == 0)
		return (SPHERE);
	else if (ft_strncmp(line, "plan", 4) == 0)
		return (PLANE);
	else if (ft_strncmp(line, "cone", 4) == 0)
		return (CONE);
	else if (ft_strncmp(line, "cyli", 4) == 0)
		return (CYLINDER);
	else if (ft_strncmp(line, "disc", 4) == 0)
		return (DISC);
	else
		ft_printf("Error reading shape from: %s\n", line);
	return (-1);
}

void	check_shape_fields(t_scene *scene, char *line, int n)
{
	double		values[N_SHAPE_VALUES];
	size_t		i;

	i = 0;
	get_fields(line, values, N_SHAPE_VALUES);
	scene->shapes[n].type = get_shape_type(line);
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
	scene->lights[n].position = ft_clamp_vec3(ft_make_vec3(values[0], values[1], values[2]), MIN_COORD, MAX_COORD);
	scene->lights[n].color = ft_clamp_rgba(ft_make_rgba(values[3], values[4], values[5], 1.0));
	scene->lights[n].type = round(ft_clamp_d0(values[6], 0, LIGHT_TYPES - 1));
	scene->lights[n].intensity = ft_clamp_d(values[7], MIN_INTENSITY, MAX_INTENSITY);
}

t_objects g_objects[N_OBJECTS] =
{
	{"sett", check_scene_fields, SETTINGS},
	{"came", check_camera_fields, CAMERA},
	{"sphe", check_shape_fields, SHAPE},
	{"plan", check_shape_fields, SHAPE},
	{"cyli", check_shape_fields, SHAPE},
	{"cone", check_shape_fields, SHAPE},
	{"poin", check_light_fields, LIGHT}
};

void exit_message(char *error)
{
	ft_putendl_fd(error, 2);
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

int		init_scene(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	int		i;
	
	scene->num_all[0] = 0;
	scene->num_all[1] = 0;
	scene->num_all[2] = 0;
	scene->num_all[3] = 0;
	scene->scene_config.filepath = file;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_message("Error loading file!");
	while (ft_get_next_line(fd, &line) > 0)
	{
		i = 0;
		while (i < N_OBJECTS)
		{
			if (ft_strncmp(line, g_objects[i].object, 4) == 0)
			{
				scene->num_all[g_objects[i].type]++;
				scene->num_objects++;
			}
			i++;
		}
		free(line);
	}
	close(fd);
	scene->num_cameras = scene->num_all[CAMERA];
	scene->num_shapes = scene->num_all[SHAPE];
	scene->num_lights = scene->num_all[LIGHT];
	scene->cameras = (t_camera*)malloc(sizeof(t_camera) * scene->num_cameras);
	scene->shapes = (t_shape*)malloc(sizeof(t_shape) * scene->num_shapes);
	scene->lights = (t_light*)malloc(sizeof(t_light) * scene->num_lights);
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

static void	print_vec3(char *s, t_vec3 v)
{
	ft_printf("%s %.3f, %.3f, %.3f", s, v.x, v.y, v.z);
}

static void	print_rgba(char *s, t_rgba c)
{
	ft_printf("%s %.3f, %.3f, %.3f %.3f", s, c.r, c.g, c.b, c.a);
}


void		print_scene_info(t_scene *scene)
{
	size_t i;

	// settings
	ft_printf("scene settings\n");
	ft_printf("\tfile: %s shadows: %d shading: %d specular: %d refraction: %d reflection: %d bounces %d\n",
		scene->scene_config.filepath,
		scene->scene_config.shadows,
		scene->scene_config.shading,
		scene->scene_config.specular,
		scene->scene_config.refraction,
		scene->scene_config.reflection, 
		scene->scene_config.bounces);
	// cameras
	ft_printf("cameras\n\t");
	i = 0;
	while (i < scene->num_cameras)
	{
		ft_printf("type: %d", scene->cameras[i].type);
		print_vec3(" pos:", scene->cameras[i].position);
		print_vec3(" target:", scene->cameras[i].target);
		print_vec3(" rot:", scene->cameras[i].rotation);
		ft_printf(" fov %.3f aspect: %.3f width: %d height %d\n", scene->cameras[i].fov, scene->cameras[i].aspect, scene->cameras[i].width, scene->cameras[i].height);
		i++;
	}

	// lights
	ft_printf("lights\n");
	i = 0;
	while (i < scene->num_lights)
	{
		ft_printf("\ttype: %d %.3f ", scene->lights[i].type, scene->lights[i].intensity);
		print_vec3("pos:", scene->lights[i].position);
		print_rgba(" color:", scene->lights[i].color);
		ft_printf("\n");
		i++;
	}

	// shapes
	ft_printf("shapes\n");
	i = 0;
	while (i < scene->num_shapes)
	{
		ft_printf("\tshape type: %d", scene->shapes[i].type);
		print_vec3(" pos:", scene->shapes[i].position);
		print_vec3(" target:", scene->shapes[i].target);
		print_vec3(" rot:", scene->shapes[i].rotation);
		print_vec3(" scale:", scene->shapes[i].scale);
		print_rgba(" color:", scene->shapes[i].color);
		ft_printf(" radius %.3f angle: %.3f opacity: %.3f\n", scene->shapes[i].radius, scene->shapes[i].angle, scene->shapes[i].opacity);
		i++;
	}
}