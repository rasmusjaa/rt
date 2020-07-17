/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 15:08:22 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/16 13:20:17 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	close_hook(t_rt *rt)
{
	ft_printf("scene %d close\n", rt->cur_scene);
	exit(0);
	rt_destroy_exit(rt, EXIT_SUCCESS);
	return (1);
}

int	expose_hook(t_rt *rt)
{
	char *file;
	t_scene_config scene_config;
	time_t modified;

	scene_config = rt->scenes[rt->cur_scene]->scene_config;
	file = scene_config.filepath;
	modified = last_modified(file);
	ft_printf("scene %d file %s expose\n", rt->cur_scene, file);
	if (scene_config.last_modified != modified) // vaihtoehtosesti checksum, raskaampi mut autosave ei haittaa
	{
		if (rt->render_task.render_started && !rt->render_task.render_finished)
		{
			ft_printf("Can't expose again yet, wait to render first\n");
			return (0);
		}
		ft_printf("Scene file has been saved, refreshing\n");
		reload_scene(rt);
	}
	return (0);
}
