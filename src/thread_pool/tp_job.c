/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_job.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:41:59 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/05 12:49:29 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

t_tp_job	*tp_job_create(tp_thread_func func, void *arg)
{
	t_tp_job *job;

	if (!func || !arg)
		return (NULL);
	if (!(job = (t_tp_job*)malloc(sizeof(t_tp_job))))
		return (NULL);
	job->func = func;
	job->arg = arg;
	return (job);
}

t_tp_job	*tp_job_get(t_tp *thread_pool)
{
	t_tp_job *job;

	if (!thread_pool)
		return (NULL);
	job = ft_queue_dequeue(thread_pool->job_queue);
	return (job);
}

void		tp_job_destroy(t_tp_job *job)
{
	if (!job)
		return ;
	free(job);
}
