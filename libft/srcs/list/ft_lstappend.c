/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:04:56 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/06 18:08:56 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *new)
{
	t_list *cur_element;

	if (*alst)
	{
		cur_element = *alst;
		while (cur_element->next)
		{
			cur_element = cur_element->next;
		}
		cur_element->next = new;
	}
	else
	{
		*alst = new;
	}
}
