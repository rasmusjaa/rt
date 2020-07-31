/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 18:05:01 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/31 18:23:40 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt.h"
#include "ft_printf.h"

void	reload_scene(t_rt *rt)
{
	t_scene *scene;
	char	*file;
	int		width;
	int		height;

	scene = rt->scenes[rt->cur_scene];
	file = scene->scene_config.filepath;
	width = scene->scene_config.width;
	height = scene->scene_config.height;
	ft_printf("old width %d height %d\n", width, height);
	destroy_scene(rt, scene);
	rt->scenes[rt->cur_scene] = read_scene(rt, file);
	rt->scenes[rt->cur_scene]->scene_config.width = width;
	rt->scenes[rt->cur_scene]->scene_config.height = height;
	ft_printf("old width %d height %d\n", rt->scenes[rt->cur_scene]->scene_config.width, rt->scenes[rt->cur_scene]->scene_config.height);
	rt->render_requested = TRUE;
}
