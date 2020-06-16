/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 15:05:29 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/16 16:11:01 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	mouse_press_hook(int button, int x, int y, t_rt *rt)
{
	t_scene *scene;

	ft_printf("scene %d, press button %d, x %d, y %d\n", rt->cur_scene, button, x, y);
	if (button == 1)
	{
		scene = rt->scenes[rt->cur_scene];
		scene->help_ray = 1;
		if (x >= 0 && y >= 0 && x < scene->scene_config.width && y < scene->scene_config.height)
		{
			t_ray r = get_camera_ray(scene, &scene->cameras[scene->cur_camera], ft_make_vec2i(x, y));
			raycast(&r, scene);
		}
		scene->help_ray = 0;
	}
	return (0);
}

int	mouse_release_hook(int button, int x, int y, t_rt *rt)
{
	ft_printf("scene %d, release button %d, x %d, y %d\n", rt->cur_scene, button, x, y);
	return (0);
}

int	mouse_move_hook(int x, int y, t_rt *rt)
{
	if (x == 0)
		ft_printf("mouse at x 0, scene %d, x %d, y %d\n", rt->cur_scene, x, y);
	return (0);
}
