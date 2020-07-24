/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 13:50:27 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/23 15:52:00 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread_pool.h"
#include "shape.h"

void	exit_message(char *error)
{
	ft_putendl_fd(error, 2);
	exit(1);
}

t_rt	*rt_init(size_t num_scenes)
{
	t_rt	*rt;

	if (!(rt = (t_rt*)malloc(sizeof(t_rt))))
		exit_message("Failed to malloc rt!");
	if (!(rt->scenes = (t_scene**)malloc(sizeof(t_scene*) * num_scenes)))
		exit_message("Failed to malloc rt->scenes!");
	rt->num_scenes = num_scenes;
	rt->cur_scene = 0;
	rt->render_task.render_started = FALSE;
	rt->render_task.render_finished = FALSE;
	rt->render_task.done_tiles = NULL;
	return (rt);
}

void	destroy_scene(t_scene *scene)
{
	size_t i;

	i = 0;
	while (i < scene->num_shapes)
	{
		if (scene->shapes[i].type == MODEL)
		{
			mesh_destroy(scene->shapes[i].mesh);
			octree_destroy(scene->shapes[i].octree);
		}
		i++;
	}
	free(scene->cameras);
	free(scene->lights);
	free(scene->shapes);
	free(scene);
}

void	rt_destroy_exit(t_rt *rt, int status)
{
	size_t i;

	i = 0;
	while (i < rt->num_scenes)
	{
		destroy_scene(rt->scenes[i]);
		i++;
	}
	free(rt->scenes);
	// call render task cleanup
	free(rt->mlx);
	free(rt);
	exit(status);
}
