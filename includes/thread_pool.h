/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:33:45 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/11 15:36:06 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_POOL_H
# define THREAD_POOL_H

# include <pthread.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_queue.h"

# define MAX_JOBS 10000

typedef void (*tp_thread_func)(void *arg);

typedef struct	s_tp_job
{
	tp_thread_func func;
	void		*arg;
}				t_tp_job;

typedef struct  s_tp
{
	pthread_mutex_t job_mutex;
	pthread_cond_t job_cond;
	pthread_cond_t working_cond;
	size_t		working_count;
	size_t      thread_count;
	int			stop;
	t_queue		*job_queue;
}               t_tp;

t_tp   *tp_create(size_t num_threads);
void	tp_destroy(t_tp *thread_pool);
int		tp_add_job(t_tp *thread_pool, tp_thread_func func, void *arg);
void	tp_wait(t_tp *thread_pool);

t_tp_job	*tp_job_create(tp_thread_func func, void *arg);
t_tp_job	*tp_job_get(t_tp *thread_pool);
void		tp_job_destroy(t_tp_job *job);

size_t	ft_get_num_procs(void);

#endif