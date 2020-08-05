/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 19:51:49 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/23 19:59:18 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"

t_stack	*ft_stack_create(size_t size, size_t item_size)
{
	t_stack *s;

	s = (t_stack*)malloc(sizeof(t_stack));
	s->size = size;
	s->item_size = item_size;
	s->items = (void*)malloc(item_size * size);
	s->ptr = 0;
	return (s);
}
