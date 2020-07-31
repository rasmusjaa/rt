/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:47:31 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/31 18:02:11 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "rt.h"
#include "thread_pool.h"
#include "ft_queue.h"
#include "render.h"
#include "ft_printf.h"
#include "mlx_image.h"

void	init_events(t_rt *rt)
{
	mlx_hook(rt->mlx->win_ptr, 2, (1L << 0), key_press_hook, rt);
	mlx_hook(rt->mlx->win_ptr, 3, (1L << 1), key_release_hook, rt);
	mlx_hook(rt->mlx->win_ptr, 4, (1L << 2), mouse_press_hook, rt);
	mlx_hook(rt->mlx->win_ptr, 5, (1L << 3), mouse_release_hook, rt);
	mlx_hook(rt->mlx->win_ptr, 6, (1L << 6), mouse_move_hook, rt);
	if (OS == 0)
		mlx_expose_hook(rt->mlx->win_ptr, expose_hook, rt);
	else
		mlx_hook(rt->mlx->win_ptr, 9, (1L << 21), expose_hook, rt);
	mlx_hook(rt->mlx->win_ptr, 17, (1L << 17), close_hook, rt);
	mlx_loop_hook(rt->mlx->mlx_ptr, update, rt);
}

int update(void *arg)
{
	t_rt			*rt;
	t_tile_job_data	*job;
	t_render_task	*task;

	rt = (t_rt*)arg;
	task = &rt->render_task;
	job = NULL;
	if (task->render_started && task->jobs == 0)
		task->render_finished = TRUE;
	while (task->render_started && task->done_tiles != NULL && !ft_queue_isempty(task->done_tiles))
	{
		pthread_mutex_lock(&task->task_mutex);
		job = (t_tile_job_data*)ft_queue_dequeue(task->done_tiles);
		if (job)
			mlx_put_image_to_window(rt->mlx->mlx_ptr, rt->mlx->win_ptr, job->mlx_img->img, job->screen_coord.x, job->screen_coord.y);
		pthread_mutex_unlock(&task->task_mutex);
	}
	if (task->render_started && task->render_finished && task->done_tiles != NULL && ft_queue_isempty(task->done_tiles))
	{
		gettimeofday(&task->end_time, NULL);
		ft_printf("render task finished in in: %.4f s\n", (double)(task->end_time.tv_usec - task->start_time.tv_usec) / 1000000 + (double)(task->end_time.tv_sec - task->start_time.tv_sec));
		cleanup_render_task(rt, task);
	}
	if (rt->render_requested)
	{
		render_scene(rt, rt->scenes[rt->cur_scene]);
		rt->render_requested = FALSE;
	}
	return (1);
}
