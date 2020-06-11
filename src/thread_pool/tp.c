/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:31:02 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/11 17:08:25 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"
#include <pthread.h>

/*
** tp_worker does most of the work and handles one thread and gets jobs
*/

static void	*tp_worker(void *arg)
{
	t_tp	*thread_pool;
	t_tp_job *job;

	thread_pool = (t_tp*)arg;
	job = NULL;
	while (1)
	{
		pthread_mutex_lock(&(thread_pool->job_mutex));
		while (ft_queue_isempty(thread_pool->job_queue) && !thread_pool->stop)
			pthread_cond_wait(&(thread_pool->job_cond), &(thread_pool->job_mutex));
		if (thread_pool->stop)
			break ;
		job = tp_job_get(thread_pool);
		thread_pool->working_count++;
		pthread_mutex_unlock(&(thread_pool->job_mutex));
		if (job)
		{
			job->func(job->arg);
			tp_job_destroy(job);
		}
		pthread_mutex_lock(&(thread_pool->job_mutex));
		thread_pool->working_count--;
		if (!thread_pool->stop && thread_pool->working_count == 0 && ft_queue_isempty(thread_pool->job_queue))
			pthread_cond_signal(&(thread_pool->working_cond));
		pthread_mutex_unlock(&(thread_pool->job_mutex));
	}
	thread_pool->thread_count--;
	pthread_cond_signal(&(thread_pool->working_cond));
	pthread_mutex_unlock(&(thread_pool->job_mutex));
	return (NULL);
}

t_tp	*tp_create(size_t num_threads)
{
	t_tp		*thread_pool;
	pthread_t	thread;
	size_t		i;

	if (num_threads == 0)
		num_threads = ft_get_num_procs() + 1;
	if (!(thread_pool = (t_tp*)malloc(sizeof(t_tp))))
		return (NULL);
	thread_pool->stop = 0;
	thread_pool->thread_count = num_threads;
	thread_pool->working_count = 0;
	pthread_mutex_init(&(thread_pool->job_mutex), NULL);
	pthread_cond_init(&(thread_pool->job_cond), NULL);
	pthread_cond_init(&(thread_pool->working_cond), NULL);
	thread_pool->job_queue = ft_queue_create(QUEUE_REF, MAX_JOBS, sizeof(t_tp_job));
	i = 0;
	while (i < num_threads)
	{
		pthread_create(&thread, NULL, tp_worker, thread_pool);
		pthread_detach(thread);
		i++;
	}
	return (thread_pool);
}

void	tp_destroy(t_tp *thread_pool)
{
	t_tp_job *job;

	if (!thread_pool)
		return ;

	pthread_mutex_lock(&(thread_pool->job_mutex));
	while (!ft_queue_isempty(thread_pool->job_queue))
	{
		job = ft_queue_dequeue(thread_pool->job_queue);
		tp_job_destroy(job);
	}
	thread_pool->stop = 1;
	pthread_cond_broadcast(&(thread_pool->job_cond));
	pthread_mutex_unlock(&(thread_pool->job_mutex));

	tp_wait(thread_pool);

	pthread_mutex_destroy(&(thread_pool->job_mutex));
	pthread_cond_destroy(&(thread_pool->job_cond));
	pthread_cond_destroy(&(thread_pool->working_cond));

	ft_queue_destroy(thread_pool->job_queue);
	free(thread_pool);
}

void	tp_wait(t_tp *thread_pool)
{
	if (!thread_pool)
		return ;

	pthread_mutex_lock(&(thread_pool->job_mutex));
	while (1)
	{
		if ((!thread_pool->stop && thread_pool->working_count != 0) || (thread_pool->stop && thread_pool->thread_count != 0))
			pthread_cond_wait(&(thread_pool->working_cond), &(thread_pool->job_mutex));
		else
			break ;
	}
	pthread_mutex_unlock(&(thread_pool->job_mutex));
}

int		tp_add_job(t_tp *thread_pool, tp_thread_func func, void *arg)
{
	t_tp_job *job;

	if (!thread_pool)
		return (0);

	if (!(job = tp_job_create(func, arg)))
		return (0);

	pthread_mutex_lock(&(thread_pool->job_mutex));
	ft_queue_enqueue(thread_pool->job_queue, job);

	// broadcast to workers that we have work to do,
	// so the first available thread picks it up.
	pthread_cond_broadcast(&(thread_pool->job_cond));
	pthread_mutex_unlock(&(thread_pool->job_mutex));

	return (1);
}
