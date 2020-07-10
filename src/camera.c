
#include "rt.h"
#include "debug.h"

void	init_camera(t_vec3 origin, t_vec3 target, t_camera *camera)
{
	if (camera->type == PERSPECTIVE)
	{
		camera->forward = ft_normalize_vec3(ft_sub_vec3(target, origin));
		camera->right = ft_normalize_vec3(ft_cross_vec3(camera->forward, ft_make_vec3(0, 1, -EPSILON)));
		camera->up = ft_normalize_vec3(ft_cross_vec3(camera->right, camera->forward));
		camera->horizontal = tan((camera->fov * M_PI / 180.0) / 2);
		camera->vertical = camera->horizontal * camera->aspect;
	}
}

t_ray	get_camera_ray(t_scene *scene, t_camera *camera, double screen_x, double screen_y)
{
	t_ray		ray;
	t_vec3		r;
	t_vec3		u;
	t_vec2		target;

	target.x = 2.0 * screen_x / (scene->scene_config.width) - 1.0;
	target.y = -2.0 * screen_y / (scene->scene_config.height) + 1.0;
	ray.origin = camera->position;
	ray.direction = camera->forward;
	r = ft_mul_vec3(camera->right, target.x * camera->horizontal);
	u = ft_mul_vec3(camera->up, target.y * camera->vertical);
	ray.direction = ft_add_vec3(ray.direction, r);
	ray.direction = ft_add_vec3(ray.direction, u);
	ray.direction = ft_normalize_vec3(ray.direction);
	return (ray);
}

// t_ray	get_camera_ray(t_scene *scene, t_camera *camera, double screen_x, double screen_y)
// {
// 	t_ray		ray;
// 	t_vec3		v1;
// 	t_vec3		v2;
// 	t_vec2		target;

// 	target.x = screen_x / (scene->scene_config.width) - 0.5;
// 	target.y = -screen_y / (scene->scene_config.height) + 0.5;
// 	ray.origin = camera->position;
// 	ray.direction = camera->forward;
// 	v1 = ft_mul_vec3(camera->right, (target.x));
// 	v2 = ft_mul_vec3(camera->up, (target.y ));
// 	ray.direction = ft_add_vec3(ray.direction, v1);
// 	ray.direction = ft_add_vec3(ray.direction, v2);
// 	ray.direction = ft_normalize_vec3(ray.direction);
// 	return (ray);
// }
