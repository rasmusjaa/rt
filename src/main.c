/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:59:56 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/30 15:39:54 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ft_printf.h"
#include "events.h"
#include "mlx.h"
#include "thread_pool.h"
#include "mlx_image.h"
#include "debug.h"

void	render_tile_job(void *data)
{
	t_tile_job_data *job_data;
	t_vec2i cur;
	t_rgba color;
	t_ray camera_ray;
	size_t si;

	job_data = (t_tile_job_data*)data;
	cur.y = job_data->screen_coord.y;
	while (cur.y < job_data->screen_coord.y + job_data->tile_size.y)
	{
		cur.x = job_data->screen_coord.x;
		while (cur.x < job_data->screen_coord.x + job_data->tile_size.x)
		{
			color = ft_make_rgba(0,0,0,1);
			if (job_data->scene->scene_config.dof)
			{
				si = 0;
				while (si < job_data->scene->scene_config.dof_samples)
				{
					camera_ray = get_camera_ray(job_data->scene, job_data->camera, cur.x, cur.y);
					color = ft_add_rgba_uc(color, raycast(&camera_ray, job_data->scene, 0));
					si++;
				}
				color = ft_div_rgba(color, job_data->scene->scene_config.dof_samples);
			}
			else
			{
				camera_ray = get_camera_ray(job_data->scene, job_data->camera, cur.x, cur.y);
				color = raycast(&camera_ray, job_data->scene, 0);
			}
			put_pixel_mlx_img(job_data->mlx_img, cur.x - job_data->screen_coord.x, cur.y - job_data->screen_coord.y, ft_get_color(ft_clamp_rgba(color)));
			cur.x++;
		}
		cur.y++;
	}
	pthread_mutex_lock(&job_data->rt->render_task.task_mutex);
	(*job_data->jobs)--;
	ft_queue_enqueue(job_data->rt->render_task.done_tiles, job_data);
	if (*job_data->jobs == 0)
	{
		ft_printf("last job done\n");
		job_data->rt->render_task.render_finished = TRUE;
	}
	pthread_mutex_unlock(&job_data->rt->render_task.task_mutex);
}

void	init_render_task(t_render_task *task, size_t res)
{
	task->render_finished = FALSE;
	task->render_started = FALSE;
	task->num_jobs = res * res;
	task->jobs = task->num_jobs;
	if (task->thread_pool)
		tp_destroy(task->thread_pool);
	task->thread_pool = tp_create(N_THREADS, task->num_jobs);
	if (!(task->job_data_block = (t_tile_job_data*)(malloc(sizeof(t_tile_job_data) * task->num_jobs))))
		exit_message("init_render_task: Failed to allocate memory for thread pool jobs!");
	task->done_tiles = ft_queue_create(QUEUE_COPY, task->num_jobs, sizeof(t_tile_job_data));
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

void	render_scene(t_rt *rt, t_scene *scene)
{
	t_camera *camera;
	t_vec2i	cur;
	t_vec2i tile_size;
	int ji;

	ft_printf("render!\n");
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
			tp_add_job(rt->render_task.thread_pool, render_tile_job, &rt->render_task.job_data_block[ji]);
			ji++;
			cur.x += tile_size.x;
		}
		cur.y += tile_size.y;
	}
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

void	hooks_and_loop(t_rt *rt)
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

	render_scene(rt, rt->scenes[rt->cur_scene]);
}

static void	init_mlx(t_rt *rt)
{
	if (!(rt->mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		exit_message("Failed to malloc mlx!");
	rt->mlx->mlx_ptr = mlx_init();
	// rt->mlx->win_ptr = mlx_new_window(rt->mlx->mlx_ptr, win_width + 300, win_height, "RT");
	// mlx_string_put(rt->mlx->mlx_ptr, rt->mlx->win_ptr, (win_width / 2) - 110, win_height / 2, 0xFFFFFF, "PRESS SPACE TO RENDER");
}

int		main(int ac, char **av)
{
	t_rt	*rt;
	int		i;

	rt = rt_init(ac - 1);
	i = 0;
	if (ac == 1)
		exit_message("Usage: RTFM!");
	init_mlx(rt);
	while (i < ac - 1)
	{
		rt->scenes[i] = read_scene(rt, av[i + 1]);
		print_scene_info(rt->scenes[i]);
		i++;
	}
	t_scene *scene = rt->scenes[rt->cur_scene];
	rt->mlx->win_ptr = mlx_new_window(rt->mlx->mlx_ptr, scene->scene_config.width + 300, scene->scene_config.width, "RT");
	hooks_and_loop(rt);
	mlx_loop(rt->mlx->mlx_ptr);
	return (0);
}
