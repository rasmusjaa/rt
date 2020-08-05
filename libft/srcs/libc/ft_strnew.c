/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:56:56 by wkorande          #+#    #+#             */
/*   Updated: 2019/10/20 17:32:38 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	if (!(str = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	ft_bzero((void*)str, size + 1);
	return (str);
}
