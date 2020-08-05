/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_enqueue.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 14:14:04 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/02 17:52:45 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"
#include "libft.h"
#include "ft_printf.h"

void	ft_queue_enqueue(t_queue *q, void *item)
{
	if (q->rear == (int)q->size - 1)
		return ;
	else
	{
		if (q->front == -1)
			q->front = 0;
		if (q->type == QUEUE_REF)
		{
			q->rear++;
			q->ref_items[q->rear] = item;
		}
		else if (q->type == QUEUE_COPY)
		{
			if (q->rear == -1)
				q->rear++;
			else
				q->rear += q->item_size;
			ft_memcpy((void*)&q->copy_items[q->rear], item, q->item_size);
		}
	}
}
