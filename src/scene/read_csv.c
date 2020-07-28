/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_csv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:08:04 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/28 19:03:11 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ft_get_next_line.h"
#include "libft.h"
#include "ft_printf.h"
#include "shape.h"
#include "obj_loader.h"
#include "mlx_image.h"
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include "texture.h"
#include "material.h"

t_shape_name_type_map g_shape_name_type_map[SHAPE_TYPES] =
{
	{PLANE_STR, PLANE},
	{SPHERE_STR, SPHERE},
	{CYL_STR, CYLINDER},
	{CONE_STR, CONE},
	{DISC_STR, DISC},
	{MODEL_STR, MODEL},
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
	double			values[N_SCENE_VALUES];
	t_scene_config	*conf;

	n = 0;
	conf = &scene->scene_config;
	get_fields(line, values, N_SCENE_VALUES);
	conf->shadows = round(ft_clamp_d0(values[0], 0, 1));
	conf->shading = round(ft_clamp_d0(values[1], 0, 1));
	conf->specular = round(ft_clamp_d0(values[2], 0, 1));
	conf->opacity = round(ft_clamp_d0(values[3], 0, 1));
	conf->refraction = round(ft_clamp_d0(values[4], 0, 1));
	conf->reflection = round(ft_clamp_d0(values[5], 0, 1));
	conf->bounces = round(ft_clamp_d(values[6], MIN_BOUNCES, MAX_BOUNCES));
	conf->width = round(ft_clamp_d(values[7], MIN_WIDTH, MAX_WIDTH));
	conf->height = round(ft_clamp_d(values[8], MIN_HEIGHT, MAX_HEIGHT));
	conf->ambient = ft_clamp_rgba(ft_make_rgba(
		values[10], values[10], values[11], values[12]));
}

void	check_camera_fields(t_scene *scene, char *line, int n)
{
	double		values[N_CAMERA_VALUES];
	t_camera	*cams;

	get_fields(line, values, N_CAMERA_VALUES);
	cams = scene->cameras;
	cams[n].position = ft_clamp_vec3(ft_make_vec3(values[0], values[1], values[2]), MIN_COORD, MAX_COORD);
	cams[n].target = ft_clamp_vec3(ft_make_vec3(values[3], values[4], values[5]), MIN_COORD, MAX_COORD);
	cams[n].rotation = ft_clamp_vec3(ft_make_vec3(-values[6], -values[7], -values[8]), 0, 360);
	cams[n].fov = ft_clamp_d(values[9], MIN_FOV, MAX_FOV);
	cams[n].type = round(ft_clamp_d0(values[10], 0, CAMERA_TYPES - 1));
	cams[n].aspect = ft_clamp_d(values[11], MIN_ASPECT, MAX_ASPECT);
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
	t_shape		*s;

	s = &scene->shapes[n];
	get_fields(line, values, N_SHAPE_VALUES);
	s->type = get_shape_type(line);
	s->name = get_shape_name(s->type);
	s->position = ft_clamp_vec3(ft_make_vec3(values[0], values[1], values[2]), MIN_COORD, MAX_COORD);
	s->target = ft_clamp_vec3(ft_make_vec3(values[3], values[4], values[5]), MIN_COORD, MAX_COORD);
	s->rotation = ft_clamp_vec3(ft_make_vec3(-values[6], -values[7], -values[8]), 0, 360);
	s->scale = ft_clamp_d(values[9], MIN_SCALE, MAX_SCALE);
	s->color = ft_clamp_rgba(ft_make_rgba(values[10], values[11], values[12], values[13]));
	s->radius = s->scale * ft_clamp_d(values[14], MIN_RADIUS, MAX_RADIUS);
	s->angle = ft_clamp_d(values[15], MIN_ANGLE, MAX_ANGLE);
	s->material_id = (int)values[16];
	s->opacity = 1.0; // temp value.. try to read opacity from material
	s->reflection = ft_clamp_d(values[17], 0, 1);
	s->refraction = ft_clamp_d(values[18], 1, 90);
	s->shine = ft_clamp_d(values[19], 0, 1);
	if (s->type == MODEL)
	{
		file_pointer = get_shape_file(line, N_SHAPE_VALUES);
		if (file_pointer == NULL)
			exit_message("no model on model line");
		ft_strcpy(file, file_pointer);
		s->mesh = obj_load(file, *s);
		s->octree = octree_create_node(s->mesh->bounds, s->mesh->num_trifaces, s->mesh->trifaces);
		ft_printf("loaded model from file %s\n", file);
	}
	else
	{
		if (s->position.x == s->target.x && s->position.y == s->target.y && s->position.z == s->target.z)
			s->target.y = s->position.y + 1;
		s->target = ft_normalize_vec3(ft_rotate_vec3(ft_sub_vec3(s->target, s->position), s->rotation));
	}
}

void	check_light_fields(t_scene *scene, char *line, int n)
{
	double		values[N_LIGHT_VALUES];
	t_light		*lights;

	lights = scene->lights;
	get_fields(line, values, N_LIGHT_VALUES);
	lights[n].position = ft_clamp_vec3(ft_make_vec3(values[0], values[1], values[2]), MIN_COORD, MAX_COORD);
	lights[n].color = ft_clamp_rgba(ft_make_rgba(values[3], values[4], values[5], 1.0));
	lights[n].type = round(ft_clamp_d0(values[6], 0, LIGHT_TYPES - 1));
	lights[n].intensity = ft_clamp_d(values[7], MIN_INTENSITY, MAX_INTENSITY);
	lights[n].radius = ft_clamp_d(values[8], 0, 5);
	lights[n].leds = round(ft_clamp_d(values[9], 2, 100));
}

void	check_material_fields(t_scene *scene, char *line, int n)
{
	double		values[N_MATERIAL_VALUES];
	t_material	*mat;

	mat = scene->materials;
	get_fields(line, values, N_MATERIAL_VALUES);
	mat[n].id = round(values[0]);
	mat[n].texture_id = round(values[1]);
	mat[n].diffuse = ft_make_rgba(values[2], values[3], values[4], values[5]);
	mat[n].specular = values[6];
	mat[n].shininess = values[7];
	mat[n].refra_index = values[8];
	mat[n].reflection = values[9];
	mat[n].opacity = values[10];
	mat[n].u_scale = values[11];
	mat[n].v_scale = values[12];
	mat[n].texture = NULL;
}

void	check_texture_fields(t_scene *scene, char *line, int n)
{
	double		values[N_TEXTURE_VALUES];
	t_texture	*tx;
	char		*temp;
	size_t		i;

	tx = scene->textures;
	get_fields(line, values, N_TEXTURE_VALUES);
	tx[n].id = round(values[0]);
	tx[n].procedural_type = round(values[1]);
	tx[n].color1 = ft_make_rgba(values[2], values[3], values[4], values[5]);
	tx[n].color2 = ft_make_rgba(values[6], values[7], values[8], values[9]);
	tx[n].color3 = ft_make_rgba(values[10], values[11], values[12], values[13]);
	ft_bzero(tx[n].file, 256);
	tx[n].img_data = NULL;
	if (!tx[n].procedural_type && (temp = get_shape_file(line, N_TEXTURE_VALUES)))
	{
		if (temp[0] != '0' && temp[0] != ';')
		{
			i = 0;
			while (temp[i] && temp[i] != ';')
				i++;
			ft_strncpy(tx[n].file, temp, i);
			tx[n].img_data = load_xpm_to_mlx_img(scene->rt->mlx, tx[n].file);
		}
	}
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
	{POINT_LIGHT_STR, check_light_fields, LIGHT},
	{MATERIAL_STR, check_material_fields, MATERIAL},
	{TEXTURE_STR, check_texture_fields, TEXTURE}
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

	// SETTINGS,
	// CAMERA,
	// SHAPE,
	// LIGHT,
	// MATERIAL,
	// TEXTURE

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
	scene->num_cameras = scene->num_all[CAMERA];
	scene->num_shapes = scene->num_all[SHAPE];
	scene->num_lights = scene->num_all[LIGHT];
	scene->num_materials = scene->num_all[MATERIAL];
	scene->num_textures = scene->num_all[TEXTURE];
	//allocate_materials(scene,scene->num_all[MATERIAL]);
	//allocate_textures(scene, scene->num_all[TEXTURE]);
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

static void	link_shapes_materials_textures(t_scene *scene)
{
	size_t		i;
	// t_material	*mater;
	// t_shape		*shape;


	i = 0;
	while (i < scene->num_materials)
	{
		scene->materials[i].texture = get_texture_by_id(scene, scene->materials[i].texture_id);
		// if (scene->materials[i].texture)
		// 	scene->materials[i].texture->img_data = load_xpm_to_mlx_img(rt->mlx, scene->materials[i].texture->file);
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
	link_shapes_materials_textures(scene);
	scene->cube_map = load_xpm_to_mlx_img(rt->mlx, "resources/cube_map.xpm");
	return (scene);
}
