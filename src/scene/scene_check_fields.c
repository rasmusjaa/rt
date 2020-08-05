/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check_fields.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 14:44:38 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 14:20:28 by wkorande         ###   ########.fr       */
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
	cams[n].position = ft_clamp_vec3(ft_make_vec3(values[0], values[1],
		values[2]), MIN_COORD, MAX_COORD);
	cams[n].target = ft_clamp_vec3(ft_make_vec3(values[3], values[4],
		values[5]), MIN_COORD, MAX_COORD);
	cams[n].rotation = ft_clamp_vec3(ft_make_vec3(-values[6], -values[7],
		-values[8]), 0, 360);
	cams[n].fov = ft_clamp_d(values[9], MIN_FOV, MAX_FOV);
	cams[n].type = round(ft_clamp_d0(values[10], 0, CAMERA_TYPES - 1));
	cams[n].aspect = ft_clamp_d(values[11], MIN_ASPECT, MAX_ASPECT);
	cams[n].focal_length = ft_clamp_d(values[12], 0, MAX_CLIP);
	cams[n].aperture = ft_clamp_d(values[13], 0.01, 10.0);
}

void	check_light_fields(t_scene *scene, char *line, int n)
{
	double		values[N_LIGHT_VALUES];
	t_light		*lights;

	lights = scene->lights;
	get_fields(line, values, N_LIGHT_VALUES);
	lights[n].position = ft_clamp_vec3(ft_make_vec3(values[0], values[1],
		values[2]), MIN_COORD, MAX_COORD);
	lights[n].color = ft_clamp_rgba(ft_make_rgba(values[3], values[4],
		values[5], 1.0));
	lights[n].type = round(ft_clamp_d0(values[6], 0, LIGHT_TYPES - 1));
	lights[n].intensity = ft_clamp_d(values[7], MIN_INTENSITY, MAX_INTENSITY);
	lights[n].radius = ft_clamp_d(values[8], 0, 5);
	lights[n].leds = round(ft_clamp_d(values[9], 2, 100));
}
