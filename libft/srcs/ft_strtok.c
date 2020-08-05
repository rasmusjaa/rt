/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:16:46 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/12 13:15:40 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_delim(char c, const char *delims)
{
	int i;

	i = 0;
	while (delims[i] != '\0')
	{
		if (delims[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	advance_ptr(char *ptr, const char *delims)
{
	int i;

	i = 0;
	while (is_delim(*ptr, delims))
	{
		ptr++;
		i++;
	}
	return (i);
}

char		*ft_strtok(char *src, const char *delims)
{
	static char	*ptr;
	char		*token;

	if (src)
	{
		src += advance_ptr(src, delims);
		ptr = src;
	}
	if (!ptr)
		return (NULL);
	token = ptr;
	while (*ptr != '\0')
	{
		if (is_delim(*ptr, delims))
		{
			*ptr++ = '\0';
			ptr += advance_ptr(ptr, delims);
			break ;
		}
		ptr++;
	}
	ptr += advance_ptr(ptr, delims);
	if (*(ptr) == '\0')
		ptr = NULL;
	return (token);
}
