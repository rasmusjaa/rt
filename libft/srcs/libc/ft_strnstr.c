/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:11:54 by wkorande          #+#    #+#             */
/*   Updated: 2019/10/16 16:50:34 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t c1;
	size_t c2;

	if (!*needle)
		return ((char*)haystack);
	c1 = 0;
	while (haystack[c1] != '\0' && c1 < len)
	{
		if (haystack[c1] == needle[0])
		{
			c2 = 0;
			while (haystack[c1 + c2] == needle[c2] && needle[c2] != '\0'\
			&& c1 + c2 < len)
			{
				if (needle[c2 + 1] == '\0')
				{
					haystack += c1;
					return ((char*)haystack);
				}
				c2++;
			}
		}
		c1++;
	}
	return (0);
}
