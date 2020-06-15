/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:33:45 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/15 15:35:02 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_POOL_H
# define THREAD_POOL_H

# include <pthread.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_queue.h"

# define MAX_JOBS 20000

typedef void (*tp_thread_func)(void *arg);

typedef struct	s_tp_job
{
	tp_thread_func func;
	void		*arg;
}				t_tp_job;

typedef struct	s_tp_queue
{
	t_tp_job	**queue;
	int			front;
	int			rear;
	size_t		size;
}				t_tp_queue;

typedef struct  s_tp
{
	pthread_mutex_t job_mutex;
	pthread_cond_t job_cond;
	pthread_cond_t working_cond;
	// size_t		working_count;
	size_t		thread_count;
	int			stop;
	t_tp_queue	*job_queue;
}				t_tp;

t_tp	*tp_create(size_t num_threads, size_t max_jobs);
void	tp_destroy(t_tp *thread_pool);
int		tp_add_job(t_tp *thread_pool, tp_thread_func func, void *arg);
void	tp_wait(t_tp *thread_pool);

t_tp_job	*tp_job_create(tp_thread_func func, void *arg);
t_tp_job	*tp_job_get(t_tp *thread_pool);
void		tp_job_destroy(t_tp_job *job);

size_t	ft_get_num_procs(void);

t_tp_queue	*tp_queue_create(size_t size);
void		tp_queue_enqueue(t_tp_queue *q, t_tp_job *job);
t_tp_job	*tp_queue_dequeue(t_tp_queue *q);
void		tp_queue_destroy(t_tp_queue *q);
int			tp_queue_isempty(t_tp_queue *q);

#endif
