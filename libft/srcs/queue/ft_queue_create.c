/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 14:11:58 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/02 18:06:41 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

t_queue	*ft_queue_create(t_q_type type, size_t size, size_t item_size)
{
	t_queue *q;

	if (!(q = malloc(sizeof(t_queue))))
		return (NULL);
	if (type == QUEUE_REF)
	{
		if (!(q->ref_items = malloc(sizeof(void*) * size)))
			return (NULL);
	}
	else if (type == QUEUE_COPY)
	{
		if (!(q->copy_items = malloc(item_size * size)))
			return (NULL);
	}
	q->type = type;
	q->size = size;
	q->item_size = item_size;
	q->front = -1;
	q->rear = -1;
	return (q);
}
