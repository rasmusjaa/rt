/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 11:39:28 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/11 16:11:07 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ft_printf.h"
#include "vector.h"

void	print_vec3(char *s, t_vec3 v)
{
	ft_printf("%s %.2f, %.2f, %.2f", s, v.x, v.y, v.z);
}

void	print_rgba(char *s, t_rgba c)
{
	ft_printf("%s %.2f, %.2f, %.2f %.2f", s, c.r, c.g, c.b, c.a);
}

void	print_scene_info(t_scene *scene)
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
	ft_printf("cameras %d\n", scene->num_cameras);
	i = 0;
	while (i < scene->num_cameras)
	{
		ft_printf("\ttype: %d", scene->cameras[i].type);
		print_vec3(" pos:", scene->cameras[i].position);
		print_vec3(" target:", scene->cameras[i].target);
		print_vec3(" rot:", scene->cameras[i].rotation);
		ft_printf(" fov %.2f aspect: %.2f\n", scene->cameras[i].fov, scene->cameras[i].aspect);
		i++;
	}

	// lights
	ft_printf("lights %d\n", scene->num_lights);
	i = 0;
	while (i < scene->num_lights)
	{
		ft_printf("\ttype: %d intensity: %.2f ", scene->lights[i].type, scene->lights[i].intensity);
		print_vec3("pos:", scene->lights[i].position);
		print_rgba(" color:", scene->lights[i].color);
		ft_printf("\n");
		i++;
	}

	// shapes
	ft_printf("shapes %d\n", scene->num_shapes);
	i = 0;
	while (i < scene->num_shapes)
	{
		ft_printf("\t%s type: %d", scene->shapes[i].name, scene->shapes[i].type);
		print_vec3(" pos:", scene->shapes[i].position);
		print_vec3(" target:", scene->shapes[i].target);
		print_vec3(" rot:", scene->shapes[i].rotation);
		print_vec3(" scale:", scene->shapes[i].scale);
		print_rgba(" color:", scene->shapes[i].color);
		ft_printf(" radius %.2f angle: %.2f opacity: %.2f\n", scene->shapes[i].radius, scene->shapes[i].angle, scene->shapes[i].opacity);
		i++;
	}
}
