/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 11:39:28 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/23 14:55:10 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "rt.h"
#include "ft_printf.h"
#include "vector.h"
#include "octree.h"
#include "shape.h"

void	print_vec3(char *s, t_vec3 v)
{
	ft_printf("%s %.2f, %.2f, %.2f\n", s, v.x, v.y, v.z);
}

void	print_rgba(char *s, t_rgba c)
{
	ft_printf("%s %.2f, %.2f, %.2f %.2f\n", s, c.r, c.g, c.b, c.a);
}

void	print_scene_info(t_scene *scene)
{
	size_t i;

	// settings
	ft_printf("scene settings\n");
	ft_printf("\tfile: %s shadows: %d shading: %d specular: %d opacity: %d refraction: %d reflection: %d bounces %d\n",
		scene->scene_config.filepath,
		scene->scene_config.shadows,
		scene->scene_config.shading,
		scene->scene_config.specular,
		scene->scene_config.opacity,
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
		ft_printf(" scale: %f\n", scene->shapes[i].scale);
		print_rgba(" color:", scene->shapes[i].color);
		ft_printf(" radius %.2f angle: %.2f opacity: %.2f\n", scene->shapes[i].radius, scene->shapes[i].angle, scene->shapes[i].opacity);
		i++;
	}
}

t_vec2i	world_to_screen_point(t_camera *camera, t_vec3 world_point, t_vec2i window_size)
{
	t_vec3	dir;
	t_vec2i	screen_point;

	dir = ft_normalize_vec3(ft_sub_vec3(world_point, camera->position));
	screen_point.x = (dir.x + 0.5) * window_size.x;
	screen_point.y = window_size.y - ((dir.y + 0.5) * window_size.y);
	return (screen_point);
}

void	draw_bounds(t_mlx *mlx, t_camera *camera, t_vec2i window_size, t_bounds b, t_rgba color)
{
	int c = ft_get_color(color);
	t_vec2i p0 = world_to_screen_point(camera, b.min, window_size);
	t_vec2i p1 = world_to_screen_point(camera, ft_make_vec3(b.max.x, b.min.y, b.min.z), window_size);
	t_vec2i p2 = world_to_screen_point(camera, ft_make_vec3(b.max.x, b.max.y, b.min.z), window_size);
	t_vec2i p3 = world_to_screen_point(camera, ft_make_vec3(b.min.x, b.max.y, b.min.z), window_size);

	t_vec2i p4 = world_to_screen_point(camera, ft_make_vec3(b.min.x, b.min.y, b.max.z), window_size);
	t_vec2i p5 = world_to_screen_point(camera, ft_make_vec3(b.max.x, b.min.y, b.max.z), window_size);
	t_vec2i p6 = world_to_screen_point(camera, b.max, window_size);
	t_vec2i p7 = world_to_screen_point(camera, ft_make_vec3(b.min.x, b.max.y, b.max.z), window_size);

	draw_line(mlx, p0, p1, c);
	draw_line(mlx, p1, p2, c);
	draw_line(mlx, p2, p3, c);
	draw_line(mlx, p3, p0, c);

	draw_line(mlx, p4, p5, c);
	draw_line(mlx, p5, p6, c);
	draw_line(mlx, p6, p7, c);
	draw_line(mlx, p7, p4, c);

	draw_line(mlx, p0, p4, c);
	draw_line(mlx, p1, p5, c);
	draw_line(mlx, p2, p6, c);
	draw_line(mlx, p3, p7, c);
}

void 	draw_octree_bounds(t_octree *o, t_mlx *mlx, t_camera *camera, t_vec2i window_size, t_rgba color)
{
	if (!o)
		return ;
	int i = 0;
	if (!(o->is_last))
	{
		while (i < NUM_CHILDREN)
		{
			draw_octree_bounds(o->children[i], mlx, camera, window_size, ft_mul_rgba(color, 0.7));
			i++;
		}
	}
	draw_bounds(mlx, camera, window_size, o->bounds, color);
}

void	draw_model_bounds(t_mlx *mlx, t_scene *scene)
{
	size_t i;
	t_vec2i window_size;

	window_size = ft_make_vec2i(scene->scene_config.width, scene->scene_config.height);

	i = 0;
	while (i < scene->num_shapes)
	{
		if (scene->shapes[i].type == MODEL)
		{
			// draw_bounds(mlx, &scene->cameras[scene->cur_camera], window_size, b);
			t_octree *o = scene->shapes[i].octree;
			draw_octree_bounds(o, mlx, &scene->cameras[scene->cur_camera], window_size, ft_make_rgba(1.0, 1.0, 1.0, 1.0));
		}
		i++;
	}
}
