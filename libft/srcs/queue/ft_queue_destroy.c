/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 14:12:52 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/21 16:28:23 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

void	ft_queue_destroy(t_queue *q)
{
	q->type == QUEUE_REF ? (free(q->ref_items)) : (free(q->copy_items));
	free(q);
}
