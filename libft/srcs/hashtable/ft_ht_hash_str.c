/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ht_hash_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 11:17:26 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/20 12:51:42 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtable.h"
#include "libft.h"

size_t	ft_ht_hash_str(const void *htptr, const void *keyptr)
{
	size_t	value;
	int		i;
	int		key_len;

	key_len = ft_strlen((char*)keyptr);
	value = 0;
	i = 0;
	while (i < key_len)
		value = value * 37 + ((char*)keyptr)[i++];
	value = value % ((t_ht*)htptr)->size;
	return (value);
}
