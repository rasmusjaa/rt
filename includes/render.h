/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:51:00 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 13:10:28 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "rt.h"
# include "vector.h"
# include <pthread.h>
# include <stdlib.h>

struct s_mlx;
struct s_scene;

typedef struct			s_tile_job_data
{
	struct s_rt			*rt;
	struct s_mlx		*mlx;
	struct s_scene		*scene;
	struct s_mlx_img	*mlx_img;
	t_vec2i				screen_coord;
	t_vec2i				tile_size;
	int					tile_index;
	int					*jobs;
	pthread_mutex_t		*task_mutex;
	struct s_camera		*camera;
}						t_tile_job_data;

typedef struct			s_render_task
{
	struct timeval		start_time;
	struct timeval		end_time;
	struct s_tp			*thread_pool;
	t_tile_job_data		*job_data_block;
	pthread_mutex_t		task_mutex;
	int					jobs;
	int					num_jobs;
	struct s_queue		*done_tiles;
	size_t				render_finished;
	size_t				render_started;
}						t_render_task;

void					render_scene(struct s_rt *rt, struct s_scene *scene);
void					render_tile(void *data);
void					init_render_task(t_render_task *task, size_t res);
void					cleanup_render_task(struct s_rt *rt,
							t_render_task *task);

#endif
