/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:59:56 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/11 17:07:442 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread_pool.h"

void	render_tile_job(void *data)
{
	t_tile_job_data *job_data;
	t_rgba tcolor;
	t_vec2i cur;
	t_vec2i tile_coord;

	job_data = (t_tile_job_data *)data;
	tile_coord = ft_make_vec2i(job_data->screen_coord.x / job_data->tile_size.x, job_data->screen_coord.y / job_data->tile_size.y);
	if (tile_coord.x % 2 == 0)
	{
		if (tile_coord.y % 2 == 0)
			tcolor = ft_make_rgba(1.0, 1.0, 1.0, 1.0);
		else
			tcolor = ft_make_rgba(0.5, 0.5, 0.5, 1.0);
	}
	else
	{
		if (tile_coord.y % 2 == 0)
			tcolor = ft_make_rgba(0.5, 0.5, 0.5, 1.0);
		else
			tcolor = ft_make_rgba(1.0, 1.0, 1.0, 1.0);
	}
	cur.y = job_data->screen_coord.y;
	while (cur.y < job_data->screen_coord.y + job_data->tile_size.y)
	{
		cur.x = job_data->screen_coord.x;
		while (cur.x < job_data->screen_coord.x + job_data->tile_size.x)
		{
			t_ray camera_ray = get_camera_ray(job_data->scene, job_data->camera, cur);
			t_rgba color = raycast(&camera_ray, job_data->scene);
			put_pixel_mlx_img(job_data->mlx_img, cur.x - job_data->screen_coord.x, cur.y - job_data->screen_coord.y, ft_get_color(color));
			cur.x++;
		}
		cur.y++;
	}
	pthread_mutex_lock(job_data->job_mutex);
	(*job_data->jobs)--;
	ft_queue_enqueue(job_data->rt->done_tiles, data);
	pthread_mutex_unlock(job_data->job_mutex);
}

void	render_scene(t_rt *rt, t_scene *scene)
{
	clock_t start, end;
	double cpu_time_used;
	t_vec2i	cur;
	t_vec2i tile_size;
	t_tile_job_data *job_data_block;
	pthread_mutex_t job_mutex;
	int num_jobs;
	int ji;
	int res;

	rt->render_finished = FALSE;
	res = 20;
	num_jobs = res * res;
	rt->tp_render = tp_create(N_THREADS, num_jobs);
	tile_size = ft_make_vec2i(scene->scene_config.width / res, scene->scene_config.height / res);
	if (!(job_data_block = (t_tile_job_data*)(malloc(sizeof(t_tile_job_data) * num_jobs))))
		exit_message("Failed to allocate memory for thread pool jobs!");
	pthread_mutex_init(&(job_mutex), NULL);

	t_camera *camera = &(scene->cameras[scene->cur_camera]);
	init_camera(camera->position, camera->target, camera);
	rt->done_tiles = ft_queue_create(QUEUE_COPY, num_jobs, sizeof(t_tile_job_data));

	start = clock();
	ji = 0;
	cur.y = 0;
	while (cur.y < scene->scene_config.height)
	{
		cur.x = 0;
		while (cur.x < scene->scene_config.width)
		{
			job_data_block[ji].rt = rt;
			job_data_block[ji].mlx = rt->mlx;
			job_data_block[ji].job_mutex = &job_mutex;
			job_data_block[ji].mlx_img = create_mlx_img(rt->mlx, tile_size.x, tile_size.y);
			job_data_block[ji].scene = scene;
			job_data_block[ji].screen_coord = cur;
			job_data_block[ji].tile_size = tile_size;
			job_data_block[ji].tile_index = ji;
			job_data_block[ji].jobs = &num_jobs;
			job_data_block[ji].camera = camera;
			tp_add_job(rt->tp_render, render_tile_job, &job_data_block[ji]);
			// ft_printf("jobs %d\n", jobs);
			// ft_putendl("added");
			ji++;
			cur.x += tile_size.x;
		}
		cur.y += tile_size.y;
	}
	while (num_jobs); // siirretään muual
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	free(job_data_block);
	ft_printf("rendered in: %.4f s\n", cpu_time_used);
	// tp_destroy(rt->tp_render);
	pthread_mutex_destroy(&job_mutex);
	rt->render_finished = TRUE;
}

int update(void *arg)
{
	t_rt			*rt;
	t_tile_job_data	*job;

	rt = (t_rt*)arg;
	job = NULL;
	while (rt->done_tiles != NULL && !ft_queue_isempty(rt->done_tiles))
	{
		job = ft_queue_dequeue(rt->done_tiles);
		if (job)
		{
			mlx_put_image_to_window(rt->mlx->mlx_ptr, rt->mlx->win_ptr, job->mlx_img->img, job->screen_coord.x, job->screen_coord.y);
			destroy_mlx_img(rt->mlx, job->mlx_img);

		}
	}
	if (rt->render_finished && rt->done_tiles != NULL && ft_queue_isempty(rt->done_tiles))
	{
		ft_queue_destroy(rt->done_tiles);
		rt->done_tiles = NULL;
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

	scene = rt->scenes[rt->cur_scene];
	file = scene->scene_config.filepath;
	destroy_scene(scene);
	rt->scenes[rt->cur_scene] = read_scene(file);
	render_scene(rt, rt->scenes[rt->cur_scene]);
}

static void	init_mlx(t_rt *rt, int win_width, int win_height)
{
	if (!(rt->mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		exit_message("Failed to malloc mlx!");
	rt->mlx->mlx_ptr = mlx_init();
	rt->mlx->win_ptr = mlx_new_window(rt->mlx->mlx_ptr, win_width, win_height, "RT");
	// rt->mlx_img = create_mlx_image(rt->mlx, win_width, win_height);
	mlx_string_put(rt->mlx->mlx_ptr, rt->mlx->win_ptr, (win_width / 2) - 110, win_height / 2, 0xFFFFFF, "PRESS SPACE TO RENDER");
}

int		main(int ac, char **av)
{
	t_rt	*rt;
	int		i;

	rt = rt_init(ac - 1);
	i = 0;
	if (ac == 1)
		exit_message("Usage:");
	while (i < ac - 1)
	{
		rt->scenes[i] = read_scene(av[i + 1]);
		print_scene_info(rt->scenes[i]);
		i++;
	}
	t_scene *scene = rt->scenes[rt->cur_scene];
	init_mlx(rt, scene->scene_config.width, scene->scene_config.height);
	hooks_and_loop(rt);
	mlx_loop(rt->mlx->mlx_ptr);
	return (0);
}
