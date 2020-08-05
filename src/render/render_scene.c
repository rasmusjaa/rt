/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:25:26 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 14:58:25 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread_pool.h"
#include "mlx_image.h"
#include "scene.h"
#include "object.h"

void	set_job_data_block(t_tile_job_data *block, t_rt *rt, t_scene *scene)
{
	t_camera	*camera;

	camera = &(scene->cameras[scene->cur_camera]);
	init_camera(camera->position, camera->target, camera, scene);
	block->rt = rt;
	block->mlx = rt->mlx;
	block->task_mutex = &rt->render_task.task_mutex;
	block->mlx_img = create_mlx_img(rt->mlx, block->tile_size.x,
		block->tile_size.y);
	block->scene = scene;
	block->jobs = &rt->render_task.jobs;
	block->camera = camera;
	tp_add_job(rt->render_task.thread_pool, render_tile, block);
}

void	render_scene(t_rt *rt, t_scene *scene)
{
	t_vec2i		cur;
	t_vec2i		tile_size;
	size_t		i;

	init_render_task(&rt->render_task, RENDER_TILE_RES);
	rt->render_task.render_started = TRUE;
	tile_size = ft_make_vec2i(scene->scene_config.width / RENDER_TILE_RES,
		scene->scene_config.height / RENDER_TILE_RES);
	gettimeofday(&rt->render_task.start_time, NULL);
	i = 0;
	cur.y = 0;
	while (cur.y < scene->scene_config.height)
	{
		cur.x = 0;
		while (cur.x < scene->scene_config.width)
		{
			rt->render_task.job_data_block[i].tile_size = tile_size;
			rt->render_task.job_data_block[i].screen_coord = cur;
			rt->render_task.job_data_block[i].tile_index = i;
			set_job_data_block(&rt->render_task.job_data_block[i], rt, scene);
			cur.x += tile_size.x;
			i++;
		}
		cur.y += tile_size.y;
	}
}
