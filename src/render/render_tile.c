/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:26:23 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/31 17:55:36 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "render.h"
#include "mlx_image.h"
#include "ft_queue.h"
#include "ft_printf.h"

void	render_tile(void *data)
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
			si = 0;
			while (si < job_data->scene->scene_config.dof_samples)
			{
				camera_ray = get_camera_ray(job_data->scene, job_data->camera, cur.x, cur.y);
				color = ft_add_rgba_uc(color, raycast(&camera_ray, job_data->scene, 0));
				si++;
			}
			if (si > 1)
				color = ft_div_rgba(color, job_data->scene->scene_config.dof_samples);
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
