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

int			get_pixel(int x, int y, t_rt *rt)
{
	if (x > y && rt)
		return (0xff0000);
	else
		return (0x00ff00);
}

void	render_tile_job(void *data)
{
	t_tile_job_data *job_data;
	int color;
	t_vec2i cur;
	t_vec2i tile_coord;

	job_data = (t_tile_job_data *)data;
	tile_coord = ft_make_vec2i(job_data->screen_coord.x / job_data->tile_size.x, job_data->screen_coord.y / job_data->tile_size.y);
	if (tile_coord.x % 2 == 0)
	{
		if (tile_coord.y % 2 == 0)
			color = 0xffffff;
		else
			color = 0xff0000;
	}
	else
	{
		if (tile_coord.y % 2 == 0)
			color = 0xff0000;
		else
			color = 0xffffff;
	}
	cur.y = job_data->screen_coord.y;
	while (cur.y < job_data->screen_coord.y + job_data->tile_size.y)
	{
		cur.x = job_data->screen_coord.x;
		while (cur.x < job_data->screen_coord.x + job_data->tile_size.x)
		{
			t_ray camera_ray = get_camera_ray(job_data->scene, job_data->camera, cur);
			t_rgba c = raycast(&camera_ray, job_data->scene);
			put_pixel_mlx_img(job_data->mlx_img,  cur.x, cur.y, ft_get_color(c));
			cur.x++;
		}
		cur.y++;
	}
	pthread_mutex_lock(job_data->job_mutex);
	(*job_data->jobs)--;
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

	rt->tp_render = tp_create(N_THREADS, MAX_JOBS);
	res = 20;
	num_jobs = res * res;
	tile_size = ft_make_vec2i(scene->scene_config.width / res, scene->scene_config.height / res);
	if (!(job_data_block = (t_tile_job_data*)(malloc(sizeof(t_tile_job_data) * num_jobs))))
		exit_message("Failed to allocate memory for thread pool jobs!");
	pthread_mutex_init(&(job_mutex), NULL);

	t_camera *camera = &(scene->cameras[scene->cur_camera]);
	init_camera(camera->position, camera->target, camera);

	start = clock();
	ji = 0;
	cur.y = 0;
	while (cur.y < scene->scene_config.height)
	{
		cur.x = 0;
		while (cur.x < scene->scene_config.width)
		{
			job_data_block[ji].job_mutex = &job_mutex;
			job_data_block[ji].mlx_img = rt->mlx_img;
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
	while (num_jobs);
	// ft_printf("%d\n", jobs);
	// while (rt->tp_render->working_count)
	// tp_wait(rt->tp_render);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	mlx_put_image_to_window(rt->mlx->mlx_ptr, rt->mlx->win_ptr, rt->mlx_img->img, 0, 0);
	free(job_data_block);
	ft_printf("rendered in: %.4f s\n", cpu_time_used);
	tp_destroy(rt->tp_render);
}

void	hooks_and_loop(t_rt *rt)
{
	mlx_hook(rt->mlx->win_ptr, 2, (1L << 0), key_press_hook, rt);
	mlx_hook(rt->mlx->win_ptr, 3, (1L << 1), key_release_hook, rt);
	mlx_hook(rt->mlx->win_ptr, 4, (1L << 2), mouse_press_hook, rt);
	mlx_hook(rt->mlx->win_ptr, 5, (1L << 3), mouse_release_hook, rt);
	mlx_hook(rt->mlx->win_ptr, 6, (1L << 6), mouse_move_hook, rt);
	mlx_hook(rt->mlx->win_ptr, 9, (1L << 21), expose_hook, rt);
	mlx_hook(rt->mlx->win_ptr, 17, (1L << 17), close_hook, rt);
	mlx_loop(rt->mlx->mlx_ptr);
}

void	refresh_scene(t_rt *rt, int scene_nb, char *file)
{
	int window_x;
	int window_y;
	t_scene *scene;

	scene = rt->scenes[scene_nb];
	// vapauta aiempi scene ja siihen liittyvat?
	scene = read_scene(file);
	window_x = scene->scene_config.width;
	window_y = scene->scene_config.height;
//	mlx_destroy_image(rt->mlx->mlx_ptr, rt->mlx_img->img);
//	rt->mlx_img = create_mlx_image(rt->mlx->mlx_ptr, window_x, window_y);
//	render_scene(rt, scene);
}

void	load_scene(t_rt *rt, int scene_nb)
{
	int window_x;
	int window_y;
	t_scene *scene;

	scene = rt->scenes[scene_nb];
	window_x = scene->scene_config.width;
	window_y = scene->scene_config.height;
	if (!(rt->mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		exit_message("Failed to malloc mlx!");
	rt->mlx->mlx_ptr = mlx_init();
	rt->mlx->win_ptr = mlx_new_window(rt->mlx->mlx_ptr, window_x, window_y, "RT");
	rt->mlx_img = create_mlx_image(rt->mlx, window_x, window_y);
	render_scene(rt, scene);
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
	load_scene(rt, rt->cur_scene);
	hooks_and_loop(rt);
	tp_destroy(rt->tp_render);
	return (0);
}
