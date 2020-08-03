/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_task.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:26:54 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 12:59:38 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ft_queue.h"
#include "thread_pool.h"
#include "mlx_image.h"

void	init_render_task(t_render_task *task, size_t res)
{
	task->render_finished = FALSE;
	task->render_started = FALSE;
	task->num_jobs = res * res;
	task->jobs = task->num_jobs;
	if (task->thread_pool)
		tp_destroy(task->thread_pool);
	task->thread_pool = tp_create(N_THREADS, task->num_jobs);
	if (!(task->job_data_block = (t_tile_job_data*)(malloc(sizeof(
			t_tile_job_data) * task->num_jobs))))
		exit_message("init_render_task: Failed to malloc thread pool jobs!");
	task->done_tiles = ft_queue_create(QUEUE_COPY, task->num_jobs,
		sizeof(t_tile_job_data));
	pthread_mutex_init(&task->task_mutex, NULL);
}

void	cleanup_render_task(t_rt *rt, t_render_task *task)
{
	int i;

	ft_queue_destroy(task->done_tiles);
	task->done_tiles = NULL;
	i = 0;
	while (i < task->num_jobs)
	{
		destroy_mlx_img(rt->mlx, task->job_data_block[i].mlx_img);
		i++;
	}
	free(task->job_data_block);
	task->job_data_block = NULL;
	tp_destroy(task->thread_pool);
	task->thread_pool = NULL;
	task->num_jobs = 0;
	pthread_mutex_destroy(&task->task_mutex);
	rt->render_task.render_started = FALSE;
}
