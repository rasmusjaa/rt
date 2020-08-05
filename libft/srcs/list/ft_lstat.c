/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 20:07:00 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/16 20:08:11 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstat(t_list *lst, unsigned int n)
{
	unsigned int c;

	if (!lst)
		return (0);
	c = 0;
	while (lst)
	{
		if (c == n)
			return (lst);
		else if (c > n)
			return (0);
		lst = lst->next;
		c++;
	}
	return (0);
}
