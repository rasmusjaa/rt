/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 23:03:26 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/08/05 16:19:07 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "debug.h"
#include "scene.h"

void	init_camera(t_vec3 origin, t_vec3 target, t_camera *cam, t_scene *scene)
{
	cam->forward = ft_normalize_vec3(ft_rotate_vec3(
		ft_sub_vec3(target, origin), cam->rotation));
	cam->right = ft_normalize_vec3(ft_cross_vec3(cam->forward,
		ft_make_vec3(0, 1, -EPSILON)));
	cam->up = ft_normalize_vec3(ft_cross_vec3(cam->right, cam->forward));
	cam->horizontal = tan((cam->fov * M_PI / 180.0) / 2);
	cam->vertical = cam->horizontal * ((double)scene->scene_config.height /
		(double)scene->scene_config.width) * cam->aspect;
}

t_vec2	random_inside_unit_circle(void)
{
	t_vec2 p;
	double r;
	double theta;

	r = sqrt((double)rand() / RAND_MAX * 2.0);
	theta = ((double)rand() / RAND_MAX * 2.0) * 2 * M_PI;
	p.x = r * cos(theta);
	p.y = r * sin(theta);
	return (p);
}

double	random_d(void)
{
	double r;

	r = ((double)rand() / RAND_MAX * 2.0 - 1.0);
	return (r);
}

void	perspective_cam(t_scene *scene, t_camera *cam, t_ray *ray,
	t_vec2 target)
{
	t_vec3	r;
	t_vec3	u;
	t_vec3	focal_point;

	r = ft_mul_vec3(cam->right, target.x * cam->horizontal);
	u = ft_mul_vec3(cam->up, target.y * cam->vertical);
	ray->direction = ft_add_vec3(ray->direction, r);
	ray->direction = ft_add_vec3(ray->direction, u);
	ray->direction = ft_normalize_vec3(ray->direction);
	if (scene->scene_config.dof && cam->focal_length > EPSILON
		&& cam->aperture > 0.01)
	{
		focal_point = ft_add_vec3(cam->position, ft_mul_vec3(ray->direction,
			cam->focal_length));
		ray->origin.x += random_d() * cam->aperture;
		ray->origin.y += random_d() * cam->aperture;
		ray->origin.z += random_d() * cam->aperture;
		ray->direction = ft_normalize_vec3(ft_sub_vec3(focal_point,
			ray->origin));
	}
}

t_ray	get_camera_ray(t_scene *scene, t_camera *cam, double screen_x,
	double screen_y)
{
	t_ray	ray;
	t_vec3	r;
	t_vec3	u;
	t_vec2	target;

	target.x = 2.0 * screen_x / (scene->scene_config.width - 1) - 1.0;
	target.y = -2.0 * screen_y / (scene->scene_config.height - 1) + 1.0;
	ray.origin = cam->position;
	ray.direction = cam->forward;
	if (cam->type == PERSPECTIVE)
		perspective_cam(scene, cam, &ray, target);
	else if (cam->type == ORTHOGRAPHIC)
	{
		r = ft_mul_vec3(cam->right, target.x * cam->horizontal
			* (cam->fov / 5.0));
		u = ft_mul_vec3(cam->up, target.y * cam->vertical * (cam->fov / 5.0));
		ray.origin = ft_add_vec3(ft_add_vec3(ray.origin, r), u);
	}
	ray.source_shape = NULL;
	ray.is_shadow = FALSE;
	return (ray);
}
