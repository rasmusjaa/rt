/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:21:14 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/15 16:35:24 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread_pool.h"

t_rt	*rt_init(size_t num_scenes)
{
	t_rt	*rt;

	if (!(rt = (t_rt*)malloc(sizeof(t_rt))))
		exit_message("Failed to malloc rt!");
	if (!(rt->scenes = (t_scene**)malloc(sizeof(t_scene*) * num_scenes)))
		exit_message("Failed to malloc rt->scenes!");
	rt->num_scenes = num_scenes;
	rt->cur_scene = 0;
	rt->done_tiles = NULL;
	rt->tp_render = NULL;
	// rt->tp_render = tp_create(N_THREADS, MAX_JOBS);

	return (rt);
}

void	rt_destroy_exit(t_rt *rt, int status)
{
	tp_destroy(rt->tp_render);
	exit(status);
}
