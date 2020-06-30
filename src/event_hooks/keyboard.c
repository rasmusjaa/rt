/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 15:06:46 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/30 12:12:34 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keys.h"

int	key_press_hook(int key, t_rt *rt)
{
	t_scene *scene = rt->scenes[rt->cur_scene];
	t_camera *camera = &(scene->cameras[scene->cur_camera]);
	t_vec3 forward = ft_normalize_vec3(ft_sub_vec3(camera->target, camera->position));
	t_vec3 right = ft_normalize_vec3(ft_cross_vec3(forward, camera->up));
	ft_printf("scene %d, press key %d\n", rt->cur_scene, key);
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT)
	{
		if (key == KEY_UP)
		{
			camera->position = ft_add_vec3(camera->position, forward);
			camera->target = ft_add_vec3(camera->target, forward);
		}
		else if (key == KEY_DOWN)
		{
			camera->position = ft_add_vec3(camera->position, ft_mul_vec3(forward, -1));
			camera->target = ft_add_vec3(camera->target, ft_mul_vec3(forward, -1));
		}
		else if (key == KEY_LEFT)
		{
			camera->position = ft_add_vec3(camera->position, ft_mul_vec3(right, -1));
			camera->target = ft_add_vec3(camera->target, ft_mul_vec3(right, -1));
		}
		else if (key == KEY_RIGHT)
		{
			camera->position = ft_add_vec3(camera->position, right);
			camera->target = ft_add_vec3(camera->target, right);
		}
		render_scene(rt, scene);
	}
	return (0);
}

int	key_release_hook(int key, t_rt *rt)
{
	ft_printf("scene %d, release key %d\n", rt->cur_scene, key);
	if (key == KEY_SPACE)
	{
		mlx_clear_window(rt->mlx->mlx_ptr, rt->mlx->win_ptr);
		render_scene(rt, rt->scenes[rt->cur_scene]);
	}
	else if (key == KEY_C)
	{
		rt->scenes[rt->cur_scene]->cur_camera++;
		if (rt->scenes[rt->cur_scene]->cur_camera > rt->scenes[rt->cur_scene]->num_cameras - 1)
			rt->scenes[rt->cur_scene]->cur_camera = 0;
		render_scene(rt, rt->scenes[rt->cur_scene]);
	}
	else if (key == KEY_S)
	{
		rt->cur_scene++;
		if (rt->cur_scene > rt->num_scenes - 1)
			rt->cur_scene = 0;
		ft_printf("selected scene: %d (%s)\n", rt->cur_scene, rt->scenes[rt->cur_scene]->scene_config.filepath);
		render_scene(rt, rt->scenes[rt->cur_scene]);
	}
	else if (key == KEY_ESC)
	{
		close_hook(rt);
	}
	return (0);
}
