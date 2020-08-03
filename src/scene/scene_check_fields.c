/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check_fields.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 14:44:38 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 16:06:16 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "object.h"
#include "shape.h"
#include "texture.h"
#include "mlx_image.h"
#include "libft.h"
#include "ft_printf.h"
#include "mesh.h"
#include "object.h"
#include "obj_loader.h"

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
		values[9], values[10], values[11], values[12]));
	conf->sky_tex_id = round(values[13]);
	conf->dof = round(ft_clamp_d0(values[14], 0, 1));
	conf->dof_samples = round(ft_clamp_d(values[15], 1, 1000));
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
	cams[n].focal_length = ft_clamp_d(values[12], 0, MAX_CLIP);
	cams[n].aperture = ft_clamp_d(values[13], 0.01, 10.0);
}

void	check_shape_fields(t_scene *scene, char *line, int n)
{
	double		values[N_SHAPE_VALUES];
	char		file[256];
	char		*file_pointer;
	t_shape		*s;
	int			i;

	s = &scene->shapes[n];
	get_fields(line, values, N_SHAPE_VALUES);
	s->type = get_shape_type(line);
	s->name = get_shape_name(s->type);
	s->position = ft_clamp_vec3(ft_make_vec3(values[0], values[1], values[2]), MIN_COORD, MAX_COORD);
	s->target = ft_add_vec3(s->position, ft_make_vec3(0, 1, 0));
	s->rotation = ft_clamp_vec3(ft_make_vec3(-values[3], -values[4], -values[5]), 0, 360);
	s->scale = ft_clamp_d(values[6], MIN_SCALE, MAX_SCALE);
	s->color = ft_clamp_rgba(ft_make_rgba(values[7], values[8], values[9], values[10]));
	s->radius = s->scale * ft_clamp_d(values[11], MIN_RADIUS, MAX_RADIUS);
	s->angle = ft_clamp_d(values[12], MIN_ANGLE, MAX_ANGLE);
	s->material_id = (int)values[13];
	s->bounds = make_shape_bounds(s->position, values);
	if (s->type == MODEL)
	{
		file_pointer = get_shape_file(line, N_SHAPE_VALUES);
		if (file_pointer == NULL)
			exit_message("no model on model line");
		i = 0;
		while(file_pointer[0 + i] != '\n' && file_pointer[0 + i] != ';' && file_pointer[0 + i] != 0)
			i++;
		ft_strncpy(file, file_pointer, i);
		file[i] = 0;
		s->mesh = obj_load(file, *s);
		s->octree = octree_create_node(s->mesh->bounds, s->mesh->num_trifaces, s->mesh->trifaces);
		ft_printf("loaded model from file %s\n", file);
	}
	else
		s->target = ft_normalize_vec3(ft_rotate_vec3(ft_sub_vec3(s->target, s->position), s->rotation));
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

	mat = &scene->materials[n];
	get_fields(line, values, N_MATERIAL_VALUES);
	mat->id = round(values[0]);
	mat->texture_id = round(values[1]);
	mat->diffuse = ft_clamp_rgba(ft_make_rgba(values[2], values[3], values[4], values[5]));
	mat->shininess = ft_clamp_d(values[6], 0, 1);
	mat->refra_index = ft_clamp_d(values[7], 1, 6);
	mat->reflection = ft_clamp_d(values[8], 0, 1);
	mat->opacity = ft_clamp_d(values[9], 0, 1);
	mat->u_scale = ft_clamp_d(values[10], 0.01, 100);
	mat->v_scale = ft_clamp_d(values[11], 0.01, 100);
	mat->explode = ft_clamp_d(values[12], 0, 5);
	mat->normal_tex_id = round(ft_clamp_d(values[13], 0, 100));
	mat->normal_mult = ft_clamp_d(values[14], 0, 90);
	mat->bump_tex_id = round(ft_clamp_d(values[15], 0, 100));
	mat->bump_mult = ft_clamp_d(values[16], 0, 100);
	mat->texture = NULL;
}

void	check_texture_fields(t_scene *scene, char *line, int n)
{
	double		values[N_TEXTURE_VALUES];
	t_texture	*tx;
	char		*file_pointer;
	size_t		i;

	tx = &scene->textures[n];
	get_fields(line, values, N_TEXTURE_VALUES);
	tx->id = round(values[0]);
	tx->procedural_type = round(values[1]);
	tx->color1 = ft_clamp_rgba(ft_make_rgba(values[2], values[3], values[4], values[5]));
	tx->color2 = ft_clamp_rgba(ft_make_rgba(values[6], values[7], values[8], values[9]));
	tx->settings = ft_clamp_vec3(ft_make_vec3(values[10], values[11], values[12]), 0, 100);
	ft_bzero(tx->file, 256);
	tx->img_data = NULL;
	tx->grad_vectors = NULL;
	if (tx->procedural_type == PERLIN)
	{
			if (perlin_init(scene->rt, tx) == -1)
				exit_message("error initializing gradient vectors");
	}
	if (!tx->procedural_type)
	{
		file_pointer = get_shape_file(line, N_TEXTURE_VALUES);
		if (file_pointer == NULL)
			exit_message("no texture on texture line");
		i = 0;
		while(file_pointer[0 + i] != '\n' && file_pointer[0 + i] != ';' && file_pointer[0 + i] != 0)
			i++;
		ft_strncpy(tx->file, file_pointer, i);
		tx->file[i] = 0;
		tx->img_data = load_xpm_to_mlx_img(scene->rt->mlx, tx->file);
	}
}

