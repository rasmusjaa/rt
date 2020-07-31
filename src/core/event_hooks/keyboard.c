/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 15:06:46 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/31 18:21:33 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "events.h"
#include "ft_printf.h"
#include "vector.h"
#include "scene.h"
#include "object.h"

static void		move_camera2(int key, t_camera *cam, t_vec3 right)
{
	if (key == KEY_RIGHT)
	{
		cam->position = ft_add_vec3(cam->position, right);
		cam->target = ft_add_vec3(cam->target, right);
	}
	else if (key == KEY_NUM_PLUS)
	{
		cam->position = ft_add_vec3(cam->position, cam->up);
		cam->target = ft_add_vec3(cam->target, cam->up);
	}
	else if (key == KEY_NUM_MINUS)
	{
		cam->position = ft_add_vec3(cam->position, ft_mul_vec3(cam->up, -1));
		cam->target = ft_add_vec3(cam->target,
			ft_mul_vec3(cam->up, -1));
	}
}

static void		move_camera(int key, t_camera *cam, t_vec3 forward,
					t_vec3 right)
{
	if (key == KEY_UP)
	{
		cam->position = ft_add_vec3(cam->position, forward);
		cam->target = ft_add_vec3(cam->target, forward);
	}
	else if (key == KEY_DOWN)
	{
		cam->position = ft_add_vec3(cam->position,
			ft_mul_vec3(forward, -1));
		cam->target = ft_add_vec3(cam->target, ft_mul_vec3(forward, -1));
	}
	else if (key == KEY_LEFT)
	{
		cam->position = ft_add_vec3(cam->position, ft_mul_vec3(right, -1));
		cam->target = ft_add_vec3(cam->target, ft_mul_vec3(right, -1));
	}
	else
		move_camera2(key, cam, right);
}

static void rotate_camera(int key, t_camera *c)
{
	if (key == KEY_NUM_4)
		c->rotation.y += 10.0;
	else if (key == KEY_NUM_6)
		c->rotation.y -= 10.0;
	else if (key == KEY_NUM_8)
		c->rotation.x -= 10.0;
	else if (key == KEY_NUM_2)
		c->rotation.x += 10.0;
}

int				key_press_hook(int key, t_rt *rt)
{
	t_scene		*scene;
	t_camera	*camera;
	t_vec3		forward;
	t_vec3		right;

	scene = rt->scenes[rt->cur_scene];
	camera = &(scene->cameras[scene->cur_camera]);
	forward = ft_normalize_vec3(ft_sub_vec3(camera->target, camera->position));
	right = ft_normalize_vec3(ft_cross_vec3(forward, camera->up));
	ft_printf("Scene %d, press key %d\n", rt->cur_scene, key);
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT ||
		key == KEY_RIGHT || key == KEY_NUM_PLUS || key == KEY_NUM_MINUS ||
		key == KEY_NUM_4 || key == KEY_NUM_6 ||
		key == KEY_NUM_8 || key == KEY_NUM_2)
	{
		if (rt->render_task.render_started && !rt->render_task.render_finished)
		{
			ft_printf("Wait for scene to load first\n");
			return (0);
		}
		move_camera(key, camera, forward, right);
		rotate_camera(key, camera);
		// render_scene(rt, scene);
		rt->render_requested = TRUE;
	}
	return (0);
}

int				key_release_hook2(int key, t_rt *rt)
{
	if (key == KEY_S)
	{
		rt->cur_scene++;
		if (rt->cur_scene > rt->num_scenes - 1)
			rt->cur_scene = 0;
		ft_printf("Selected scene: %d (%s)\n", rt->cur_scene,
			rt->scenes[rt->cur_scene]->scene_config.filepath);
		// render_scene(rt, rt->scenes[rt->cur_scene]);
		rt->render_requested = TRUE;
	}
	else if (key == KEY_X)
	{
		rt->scenes[rt->cur_scene]->scene_config.colorize++;
		if (rt->scenes[rt->cur_scene]->scene_config.colorize > COLORIZES - 1)
			rt->scenes[rt->cur_scene]->scene_config.colorize = 0;
		// render_scene(rt, rt->scenes[rt->cur_scene]);
		rt->render_requested = TRUE;
	}
	else if (key == KEY_ESC)
		rt_destroy_exit(rt, EXIT_SUCCESS);
	return (0);
}

int				key_release_hook(int key, t_rt *rt)
{
	ft_printf("Scene %d, release key %d\n", rt->cur_scene, key);
	if (rt->render_task.render_started && !rt->render_task.render_finished)
	{
		ft_printf("Wait for scene to load first\n");
		return (0);
	}
	else if (key == KEY_SPACE)
	{
		mlx_clear_window(rt->mlx->mlx_ptr, rt->mlx->win_ptr);
		// render_scene(rt, rt->scenes[rt->cur_scene]);
		rt->render_requested = TRUE;
	}
	else if (key == KEY_C)
	{
		rt->scenes[rt->cur_scene]->cur_camera++;
		if (rt->scenes[rt->cur_scene]->cur_camera >
				rt->scenes[rt->cur_scene]->num_cameras - 1)
			rt->scenes[rt->cur_scene]->cur_camera = 0;
		// render_scene(rt, rt->scenes[rt->cur_scene]);
		rt->render_requested = TRUE;
	}
	else
		return (key_release_hook2(key, rt));
	return (0);
}
