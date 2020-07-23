
#include "rt.h"
#include "debug.h"

void	init_camera(t_vec3 origin, t_vec3 target, t_camera *camera, t_scene *scene)
{
	camera->forward = ft_normalize_vec3(ft_rotate_vec3(ft_sub_vec3(target, origin), camera->rotation));
	camera->right = ft_normalize_vec3(ft_cross_vec3(camera->forward, ft_make_vec3(0, 1, -EPSILON)));
	camera->up = ft_normalize_vec3(ft_cross_vec3(camera->right, camera->forward));
	camera->horizontal = tan((camera->fov * M_PI / 180.0) / 2);
	camera->aspect = camera->aspect * (double)scene->scene_config.width / (double)scene->scene_config.height;
	camera->vertical = camera->horizontal / camera->aspect;
}

t_ray get_camera_ray(t_scene *scene, t_camera *camera, double screen_x, double screen_y)
{
	t_ray ray;
	t_vec3 r;
	t_vec3 u;
	t_vec2 target;

	if (camera->type == PERSPECTIVE)
	{
		target.x = 2.0 * screen_x / (scene->scene_config.width - 1) - 1.0;
		target.y = -2.0 * screen_y / (scene->scene_config.height - 1) + 1.0;
		ray.origin = camera->position;
		ray.direction = camera->forward;
		r = ft_mul_vec3(camera->right, target.x * camera->horizontal);
		u = ft_mul_vec3(camera->up, target.y * camera->vertical);
		ray.direction = ft_add_vec3(ray.direction, r);
		ray.direction = ft_add_vec3(ray.direction, u);
		ray.direction = ft_normalize_vec3(ray.direction);
	}
	// else if (camera->type == ORTHOGRAPHIC)
	// {
	// 	target.x = 2.0 * screen_x / (scene->scene_config.width - 1) - 1.0;
	// 	target.y = -2.0 * screen_y / (scene->scene_config.height - 1) + 1.0;
	// 	ray.direction = camera->forward;
	// 	r = ft_mul_vec3(camera->right, target.x * camera->horizontal * (camera->fov / 5.0));
	// 	u = ft_mul_vec3(camera->up, target.y * camera->vertical * (camera->fov / 5.0));
	// 	ray.origin = camera->position;
	// 	ray.origin = ft_add_vec3(ray.origin, r);
	// 	ray.origin = ft_add_vec3(ray.origin, u);
	// }
	else
	{
		double x = 180.0 - ((screen_x / scene->scene_config.width) * 360.0);
		double y = 180.0 - ((screen_y / scene->scene_config.height) * 360.0);
		t_vec3 v = ft_rotate_vec3(camera->forward, ft_make_vec3(y, x, 0.0));
		ray.origin = camera->position;
		ray.direction = ft_normalize_vec3(v);
	}
	ray.source_shape = NULL;
	ray.is_shadow = FALSE;
	return (ray);
}
