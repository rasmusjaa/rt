/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:52:58 by wkorande          #+#    #+#             */
/*   Updated: 2019/10/15 16:54:59 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int		c;
	char	*d;
	char	*s;
	int		dest_len;

	d = dst;
	s = (char*)src;
	c = dstsize;
	while (c-- != 0 && *d != '\0')
		d++;
	dest_len = d - dst;
	c = dstsize - dest_len;
	if (c == 0)
		return (dest_len + ft_strlen(src));
	while (*s != '\0')
	{
		if (c != 1)
		{
			*d++ = *s;
			c--;
		}
		s++;
	}
	*d = '\0';
	return (dest_len + (s - src));
}
