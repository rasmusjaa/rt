/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:25:26 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/31 18:18:45 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread_pool.h"
#include "mlx_image.h"
#include "scene.h"
#include "object.h"

void	render_scene(t_rt *rt, t_scene *scene)
{
	t_camera *camera;
	t_vec2i	cur;
	t_vec2i tile_size;
	int ji;

	init_render_task(&rt->render_task, RENDER_TILE_RES);
	rt->render_task.render_started = TRUE;
	tile_size = ft_make_vec2i(scene->scene_config.width / RENDER_TILE_RES, scene->scene_config.height / RENDER_TILE_RES);
	camera = &(scene->cameras[scene->cur_camera]);
	init_camera(camera->position, camera->target, camera, scene);
	gettimeofday(&rt->render_task.start_time, NULL);
	ji = 0;
	cur.y = 0;
	while (cur.y < scene->scene_config.height)
	{
		cur.x = 0;
		while (cur.x < scene->scene_config.width)
		{
			rt->render_task.job_data_block[ji].rt = rt;
			rt->render_task.job_data_block[ji].mlx = rt->mlx;
			rt->render_task.job_data_block[ji].task_mutex = &rt->render_task.task_mutex;
			rt->render_task.job_data_block[ji].mlx_img = create_mlx_img(rt->mlx, tile_size.x, tile_size.y);
			rt->render_task.job_data_block[ji].scene = scene;
			rt->render_task.job_data_block[ji].screen_coord = cur;
			rt->render_task.job_data_block[ji].tile_size = tile_size;
			rt->render_task.job_data_block[ji].tile_index = ji;
			rt->render_task.job_data_block[ji].jobs = &rt->render_task.jobs;
			rt->render_task.job_data_block[ji].camera = camera;
			tp_add_job(rt->render_task.thread_pool, render_tile, &rt->render_task.job_data_block[ji]);
			ji++;
			cur.x += tile_size.x;
		}
		cur.y += tile_size.y;
	}
}
