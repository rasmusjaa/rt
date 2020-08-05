/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:02:35 by wkorande          #+#    #+#             */
/*   Updated: 2019/10/22 11:00:24 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	c;

	len = ft_strlen(str);
	i = 0;
	while (i < len - 1)
	{
		c = str[len - 1];
		str[len - 1] = str[i];
		str[i] = c;
		len--;
		i++;
	}
	return (str);
}
