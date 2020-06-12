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

// static void	image_set(int x, int y, t_rt *rt, int color)
// {
// 	t_camera 	camera;

// 	camera = rt->scenes[rt->cur_scene]->cameras[rt->scenes[rt->cur_scene]->cur_camera];
// 	*(int*)(rt->mlx->data_addr + (((y * camera.width) + x) * rt->mlx->bpp)) = color;
// }

int			get_pixel(int x, int y, t_rt *rt)
{
	if (x > y && rt)
		return (0xff0000);
	else
		return (0x00ff00);
}

typedef struct	s_job_data
{
	t_ray		ray;		// camera ray
	t_scene		*scene;		// scene we check want to raytrace
	t_mlx_img	*mlx_img; 	// the image the job writes result to
	t_vec2i		screen_coord;
	t_vec2i		tile_size;
	int			tile_index;
}				t_job_data;

void	raycast(void *data)
{
	t_job_data *job_data;
	int color;
	t_vec2i cur;
	t_vec2i tile_coord;

	job_data = (t_job_data *)data;
	tile_coord = ft_make_vec2i(job_data->screen_coord.x / job_data->tile_size.x, job_data->screen_coord.y / job_data->tile_size.y);
	if (tile_coord.x % 2 == 0)
	{
		if (tile_coord.y % 2 == 0)
			color = 0xffffff;
		else
			color = 0;
	}
	else
	{
		if (tile_coord.y % 2 == 0)
			color = 0;
		else
			color = 0xffffff;
	}

	cur.y = job_data->screen_coord.y;
	while (cur.y < job_data->screen_coord.y + job_data->tile_size.y)
	{
		cur.x = job_data->screen_coord.x;
		while (cur.x < job_data->screen_coord.x + job_data->tile_size.x)
		{
			put_pixel_mlx_img(job_data->mlx_img,  cur.x, cur.y, color);
			cur.x++;
		}
		cur.y++;
	}
	if (cur.x == 800 && cur.y == 600)
		ft_printf("last tile\n");
}

void	render_scene(t_rt *rt, t_scene *scene)
{
	clock_t start, end;
	double cpu_time_used;
	t_vec2i	cur;
	t_vec2i tile_size;
	t_tp *tp;
	t_job_data *job_block;
	int ji;
	int res;

	res = 20;
	tile_size = ft_make_vec2i(scene->scene_config.width / res, scene->scene_config.height / res);
	if (!(job_block = (t_job_data*)(malloc(sizeof(t_job_data) * tile_size.x * tile_size.y))))
		exit_message("Failed to allocate memory for thread pool jobs!");
	tp = tp_create(N_THREADS);
	start = clock();
	ji = 0;
	cur.y = 0;
	while (cur.y < scene->scene_config.height)
	{
		cur.x = 0;
		while (cur.x < scene->scene_config.width)
		{
			job_block[ji].mlx_img = rt->mlx_img;
			job_block[ji].scene = scene;
			job_block[ji].screen_coord = cur;
			job_block[ji].tile_size = tile_size;
			job_block[ji].tile_index = ji;
			tp_add_job(tp, raycast, &job_block[ji]);
			ji++;
			cur.x += tile_size.x;
		}
		mlx_put_image_to_window(rt->mlx->mlx_ptr, rt->mlx->win_ptr, rt->mlx_img->img, 0, 0);
		cur.y += tile_size.y;
	}
	tp_wait(tp);
	tp_destroy(tp);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	mlx_put_image_to_window(rt->mlx->mlx_ptr, rt->mlx->win_ptr, rt->mlx_img->img, 0, 0);
	free(job_block);
	ft_printf("rendered in: %.4f s\n", cpu_time_used);
}

/*

void		*draw_view(void *data)
{
	int			y;
	int			x;
	int			color;
	t_rt		*rt;
	t_thread	*thread;
	t_camera 	camera;

	thread = (t_thread *)data;
	rt = (t_rt *)thread->rt;
	camera = rt->scenes[rt->cur_scene]->cameras[rt->scenes[rt->cur_scene]->cur_camera];
	color = 0xffffff;
	y = thread->thread;
	while (y < camera.height)
	{
		x = 0;
		while (x < camera.width)
		{
			color = get_pixel(x, y, rt);
			image_set(x, y, rt, color);
			x++;
		}
		y += N_THREADS;
	}
	return (thread);
}

void	multi_thread(t_rt *rt)
{
	pthread_t	*thread_group;
	t_thread	*threads[N_THREADS];
	int			i;

	thread_group = malloc(sizeof(pthread_t) * N_THREADS);
	i = 0;
	while (i < N_THREADS)
	{
		threads[i] = malloc(sizeof(t_thread));
		threads[i]->rt = rt;
		threads[i]->thread = i;
		pthread_create(&thread_group[i], NULL, draw_view, threads[i]);
		i++;
	}
	i = 0;
	while (i < N_THREADS)
	{
		pthread_join(thread_group[i], NULL);
		free(threads[i]);
		i++;
	}
	free(thread_group);
	mlx_put_image_to_window(rt->mlx->mlx_ptr, rt->mlx->win_ptr, rt->mlx->img_ptr, 0, 0);
	//add_texts(rt);
}
*/

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
	// rt->mlx->img_ptr = mlx_new_image(rt->mlx->mlx_ptr, window_x, window_y);
	// rt->mlx->data_addr = mlx_get_data_addr(rt->mlx->img_ptr,
	// 	&rt->mlx->bpp, &rt->mlx->size_line, &rt->mlx->endian);
	// rt->mlx->bpp /= 8;
	rt->mlx_img = create_mlx_image(rt->mlx, window_x, window_y);
	render_scene(rt, scene);
}

static t_rt	*init_rt(size_t num_scenes)
{
	t_rt	*rt;

	if (!(rt = (t_rt*)malloc(sizeof(t_rt))))
		exit_message("Failed to malloc rt!");
	if (!(rt->scenes = (t_scene**)malloc(sizeof(t_scene*) * num_scenes)))
		exit_message("Failed to malloc rt->scenes!");
	rt->num_scenes = num_scenes;
	rt->cur_scene = 0;
	return (rt);
}

int		main(int ac, char **av)
{
	t_rt	*rt;
	int		i;

	rt = init_rt(ac - 1);
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
	return (0);
}
