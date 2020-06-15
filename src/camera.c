
#include "rt.h"

void	init_camera(t_vec3 origin, t_vec3 target, t_camera *camera)
{
	if (camera->type == PERSPECTIVE)
	{
		camera->forward = ft_normalize_vec3(ft_sub_vec3(target, origin));
		camera->right = ft_normalize_vec3(ft_cross_vec3(camera->forward, ft_make_vec3(0, 1, -0.00001)));
		camera->up = ft_normalize_vec3(ft_cross_vec3(camera->right, camera->forward));
		camera->horizontal = tan((camera->fov * M_PI / 180.0) / 2);
		camera->vertical = camera->horizontal * camera->aspect;
	}
}

t_ray	get_camera_ray(t_scene *scene, t_camera *camera, t_vec2i screen_coord)
{
	t_ray		ray;
	t_vec3		v1;
	t_vec3		v2;
	t_vec2		target;

	target.x = 2.0 * screen_coord.x / (scene->scene_config.width - 1) - 1.0;
	target.y = -2.0 * screen_coord.y / (scene->scene_config.height - 1) + 1;
	ray.origin = camera->position;
	ray.direction = camera->forward;
	v1 = ft_mul_vec3(camera->right, (target.x * camera->vertical));
	v2 = ft_mul_vec3(camera->up, (target.y * camera->horizontal));
	ray.direction = ft_add_vec3(ray.direction, v1);
	ray.direction = ft_add_vec3(ray.direction, v2);
	ray.direction = ft_normalize_vec3(ray.direction);
	return (ray);
}

    // t_vector		target;
	// t_ray			ray;
	// t_intersection	ix;

	// target.x = 2.0 * x / (mlx->img_width - 1) - 1.0;
	// target.y = -2.0 * y / (mlx->img_height - 1) + 1;
	// ray = camera_ray(mlx->camera, target);
	// ix = get_intersection(ray, mlx);
