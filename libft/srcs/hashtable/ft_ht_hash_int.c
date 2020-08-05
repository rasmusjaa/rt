/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ht_hash_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 12:08:49 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/02 17:54:54 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtable.h"
#include "libft.h"
#include "ft_printf.h"

size_t	ft_ht_hash_int(const void *htptr, const void *keyptr)
{
	size_t	value;

	value = (size_t)*(int*)keyptr;
	if (value >= ((t_ht*)htptr)->size)
	{
		ft_printf("ft_ht_hash_int: overflow with pos %d in table size %d\n",\
			value, ((t_ht*)htptr)->size);
		return (0);
	}
	return (value);
}
