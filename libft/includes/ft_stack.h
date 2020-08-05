/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 19:52:14 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/02 18:02:55 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_H
# define FT_STACK_H

# include <stdlib.h>

typedef struct	s_stack
{
	size_t		size;
	size_t		item_size;
	void		*items;
	size_t		ptr;
}				t_stack;

t_stack			*ft_stack_create(size_t size, size_t item_size);
void			ft_stack_push(t_stack *s, void *item);
void			*ft_stack_pop(t_stack *s);
int				ft_stack_isempty(t_stack *s);
void			ft_stack_destroy(t_stack *s);

#endif
