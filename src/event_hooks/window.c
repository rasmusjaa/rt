/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 15:08:22 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/09 15:23:36 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	close_hook(t_rt *rt)
{
	ft_printf("scene %d close\n", rt->cur_scene);
	exit(0);
	return (0);
}

int	expose_hook(t_rt *rt)
{
	char *file;

	file = rt->scenes[rt->cur_scene]->scene_config.filepath;
	// if file on muuttunut
	refresh_scene(rt, rt->cur_scene, file);
	ft_printf("scene %d file %s expose\n", rt->cur_scene, file);
	return (0);
}
