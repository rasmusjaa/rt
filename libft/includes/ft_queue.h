/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 16:16:58 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/02 18:06:08 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_QUEUE_H
# define FT_QUEUE_H

# include <stdlib.h>

typedef enum	e_q_type
{
	QUEUE_REF,
	QUEUE_COPY
}				t_q_type;

typedef struct	s_queue
{
	t_q_type	type;
	size_t		size;
	size_t		item_size;
	void		**ref_items;
	char		*copy_items;
	int			front;
	int			rear;
}				t_queue;

t_queue			*ft_queue_create(t_q_type type, size_t size, size_t item_size);
void			ft_queue_destroy(t_queue *q);
int				ft_queue_isempty(t_queue *q);
void			ft_queue_enqueue(t_queue *q, void *item);
void			*ft_queue_dequeue(t_queue *q);
void			ft_queue_print(t_queue *q, void (*print_item)(void*));
void			ft_queue_print_item_int(void *item);

#endif
