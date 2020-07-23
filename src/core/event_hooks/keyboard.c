/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 15:06:46 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/23 14:54:09 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "events.h"
#include "ft_printf.h"
#include "vector.h"

static void		move_camera2(int key, t_camera *camera, t_vec3 right)
{
	if (key == KEY_RIGHT)
	{
		camera->position = ft_add_vec3(camera->position, right);
		camera->target = ft_add_vec3(camera->target, right);
	}
	else if (key == KEY_NUM_PLUS)
	{
		camera->position = ft_add_vec3(camera->position, camera->up);
		camera->target = ft_add_vec3(camera->target, camera->up);
	}
	else if (key == KEY_NUM_MINUS)
	{
		camera->position = ft_add_vec3(camera->position, ft_mul_vec3(camera->up, -1));
		camera->target = ft_add_vec3(camera->target,
			ft_mul_vec3(camera->up, -1));
	}
}

static void		move_camera(int key, t_camera *camera, t_vec3 forward,
					t_vec3 right)
{
	if (key == KEY_UP)
	{
		camera->position = ft_add_vec3(camera->position, forward);
		camera->target = ft_add_vec3(camera->target, forward);
	}
	else if (key == KEY_DOWN)
	{
		camera->position = ft_add_vec3(camera->position,
			ft_mul_vec3(forward, -1));
		camera->target = ft_add_vec3(camera->target, ft_mul_vec3(forward, -1));
	}
	else if (key == KEY_LEFT)
	{
		camera->position = ft_add_vec3(camera->position, ft_mul_vec3(right, -1));
		camera->target = ft_add_vec3(camera->target, ft_mul_vec3(right, -1));
	}
	else
		move_camera2(key, camera, right);
}

int				key_press_hook(int key, t_rt *rt)
{
	t_scene *scene = rt->scenes[rt->cur_scene];
	t_camera *camera = &(scene->cameras[scene->cur_camera]);
	t_vec3 forward = ft_normalize_vec3(ft_sub_vec3(
		camera->target, camera->position));
	t_vec3 right = ft_normalize_vec3(ft_cross_vec3(forward, camera->up));
	ft_printf("Scene %d, press key %d\n", rt->cur_scene, key);
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT ||
		key == KEY_RIGHT || key == KEY_NUM_PLUS || key == KEY_NUM_MINUS)
	{
		if (rt->render_task.render_started && !rt->render_task.render_finished)
		{
			ft_printf("Wait for scene to load first\n");
			return (0);
		}
		move_camera(key, camera, forward, right);
		render_scene(rt, scene);
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
		render_scene(rt, rt->scenes[rt->cur_scene]);
	}
	else if (key == KEY_X)
	{
		rt->scenes[rt->cur_scene]->scene_config.colorize++;
		if (rt->scenes[rt->cur_scene]->scene_config.colorize > COLORIZES - 1)
			rt->scenes[rt->cur_scene]->scene_config.colorize = 0;
		render_scene(rt, rt->scenes[rt->cur_scene]);
	}
	else if (key == KEY_ESC)
		close_hook(rt);
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
		render_scene(rt, rt->scenes[rt->cur_scene]);
	}
	else if (key == KEY_C)
	{
		rt->scenes[rt->cur_scene]->cur_camera++;
		if (rt->scenes[rt->cur_scene]->cur_camera >
				rt->scenes[rt->cur_scene]->num_cameras - 1)
			rt->scenes[rt->cur_scene]->cur_camera = 0;
		render_scene(rt, rt->scenes[rt->cur_scene]);
	}
	else
		return(key_release_hook2(key, rt));
	return (0);
}
