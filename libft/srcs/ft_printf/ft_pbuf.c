/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pbuf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:38:30 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/30 23:12:43 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

t_p_buf	*ft_create_p_buf(char *dest)
{
	t_p_buf *pbuf;

	if (!(pbuf = (t_p_buf*)malloc(sizeof(t_p_buf))))
		return (NULL);
	pbuf->start = dest;
	pbuf->at = dest;
	pbuf->size = 0;
	return (pbuf);
}

int		ft_resize_p_buf(t_p_buf *pbuf)
{
	int		oldsize;
	int		size;
	char	*tmp;

	oldsize = pbuf->size;
	size = pbuf->size * 2;
	if (!(tmp = (char*)malloc(sizeof(char) * size)))
		return (0);
	tmp = ft_memcpy(tmp, pbuf->start, pbuf->size);
	free(pbuf->start);
	pbuf->start = tmp;
	pbuf->at = tmp + oldsize;
	pbuf->size = size;
	return (1);
}
