/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:22:17 by wkorande          #+#    #+#             */
/*   Updated: 2019/10/20 17:42:17 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*trim;
	int		beg;
	int		end;
	int		len;

	if (!s)
		return (NULL);
	beg = 0;
	while (s[beg] == ' ' || s[beg] == '\n' || s[beg] == '\t')
		beg++;
	end = ft_strlen(s) - 1;
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
		end--;
	len = end - beg + 1;
	if (len < 0)
		len = 0;
	if (!(trim = (char*)malloc(len + 1)))
		return (NULL);
	trim = ft_strncpy(trim, (char*)s + beg, len);
	trim[len] = '\0';
	return (trim);
}
