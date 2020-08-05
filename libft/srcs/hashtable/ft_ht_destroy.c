/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ht_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 18:41:08 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/23 19:03:11 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtable.h"

void	ft_ht_destroy(t_ht *ht)
{
	size_t i;

	i = 0;
	while (i < ht->size)
	{
		if (ht->entries[i])
			ft_ht_del(ht, ht->entries[i]->key);
		i++;
	}
	free(ht->entries);
	free(ht);
}
