/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 16:47:49 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/15 17:45:07 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread_pool.h"

t_tp_queue	*tp_queue_create(size_t size)
{
	t_tp_queue *q;

	if (!(q = (t_tp_queue*)malloc(sizeof(t_tp_queue))))
	{
		ft_printf("Couldn't malloc tp_queue!\n");
		return (NULL);
	}
	q->front = -1;
	q->rear = -1;
	q->size = size;
	if (!(q->queue = (t_tp_job**)malloc(sizeof(t_tp_job*) * size)))
	{
		ft_printf("Couldn't malloc tp_jobs!\n");
		return (NULL);
	}
	return (q);
}

void	tp_queue_enqueue(t_tp_queue *q, t_tp_job *job)
{
	if (q->rear == (int)q->size - 1)
	{
		ft_printf("Job queue full!\n");
		return ;
	}
	else
	{
		if (q->front == -1)
			q->front = 0;
		q->rear++;
		q->queue[q->rear] = job;
	}
}

t_tp_job	*tp_queue_dequeue(t_tp_queue *q)
{
	t_tp_job *job;

	if (tp_queue_isempty(q))
	{
		ft_printf("Job queue empty!\n");
		job = NULL;
	}
	else
	{
		job = q->queue[q->front];
		q->front++;
		if (q->front > q->rear)
		{
			q->front = -1;
			q->rear = -1;
		}
	}
	return (job);
}

void		tp_queue_destroy(t_tp_queue *q)
{
	free(q->queue);
	free(q);
}

int			tp_queue_isempty(t_tp_queue *q)
{
	return (q->rear == -1); // tan funktion vois mahollisesti karsii kun on vaan yhes if ehdossa samal taval kun full
}
