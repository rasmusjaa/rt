/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 19:59:30 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/02 17:51:42 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "libft.h"
#include "ft_printf.h"

void	ft_stack_push(t_stack *s, void *item)
{
	if (s->ptr >= (s->size * s->item_size))
	{
		ft_printf("ft_stack_push: stack overflow!\n");
		return ;
	}
	ft_memcpy(s->items + s->ptr, item, s->item_size);
	s->ptr += s->item_size;
}
