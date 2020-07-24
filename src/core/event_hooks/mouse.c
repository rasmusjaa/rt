/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 15:05:29 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/23 14:55:10 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ft_printf.h"

int	mouse_press_hook(int button, int x, int y, t_rt *rt)
{
	t_scene *scene;
	t_ray	r;

	ft_printf("Press button %d, x %d, y %d\n", button, x, y);
	if (button == 1 && rt->render_task.render_finished)
	{
		scene = rt->scenes[rt->cur_scene];
		scene->help_ray = 1;
		if (x >= 0 && y >= 0 && x < scene->scene_config.width
			&& y < scene->scene_config.height)
		{
			r = get_camera_ray(scene, &scene->cameras[scene->cur_camera], x, y);
			raycast(&r, scene, 0);
		}
		scene->help_ray = 0;
	}
	return (0);
}

int	mouse_release_hook(int button, int x, int y, t_rt *rt)
{
	ft_printf("Scene %d, release button %d, x %d, y %d\n",
		rt->cur_scene, button, x, y);
	return (0);
}

int	mouse_move_hook(int x, int y, t_rt *rt)
{
	if (x == 0 && y == 0)
		ft_printf("Scene %d, x %d, y %d\n", rt->cur_scene, x, y);
	return (0);
}
