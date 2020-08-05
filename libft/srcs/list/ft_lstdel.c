/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:55:31 by wkorande          #+#    #+#             */
/*   Updated: 2019/10/20 18:04:18 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *temp;

	if (!alst || !*alst || !del)
		return ;
	while (*alst)
	{
		temp = *alst;
		*alst = (*alst)->next;
		del(temp->content, temp->content_size);
		free(temp);
	}
	*alst = NULL;
}
