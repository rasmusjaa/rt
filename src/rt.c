/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 13:50:27 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/09 19:22:50 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread_pool.h"

t_rt	*rt_init(size_t num_scenes)
{
	t_rt	*rt;

	if (!(rt = (t_rt*)malloc(sizeof(t_rt))))
		exit_message("Failed to malloc rt!");
	if (!(rt->scenes = (t_scene**)malloc(sizeof(t_scene*) * num_scenes)))
		exit_message("Failed to malloc rt->scenes!");
	rt->num_scenes = num_scenes;
	rt->cur_scene = 0;
	// rt->done_tiles = NULL;
	// rt->tp_render = NULL;
	// rt->render_finished = FALSE;
	// rt->num_render_jobs = 0;
	// rt->job_data_block = NULL;
	// pthread_mutex_init(&rt->job_mutex, NULL);
	rt->render_task.render_started = FALSE;
	return (rt);
}

void	destroy_scene(t_scene *scene)
{
	size_t i;

	i = 0;
	while (i < scene->num_shapes)
	{
		if (scene->shapes[i].type == MODEL)
			mesh_destroy(scene->shapes[i].mesh);
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
