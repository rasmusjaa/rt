/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_dequeue.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 14:14:59 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/02 18:18:28 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

void	*ft_queue_dequeue(t_queue *q)
{
	void *item;

	item = NULL;
	if (ft_queue_isempty(q))
		item = NULL;
	else
	{
		if (q->type == QUEUE_REF)
			item = q->ref_items[q->front];
		else if (q->type == QUEUE_COPY)
			item = (void*)&q->copy_items[q->front];
		if (q->type == QUEUE_REF)
			q->front++;
		else if (q->type == QUEUE_COPY)
			q->front += q->item_size;
		if (q->front > q->rear)
		{
			q->front = -1;
			q->rear = -1;
		}
	}
	return (item);
}
