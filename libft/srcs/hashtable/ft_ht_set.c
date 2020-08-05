/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ht_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 11:10:47 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/02 17:53:40 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtable.h"
#include <stdlib.h>
#include "libft.h"

static t_ht_e	*ft_ht_make_entry(t_ht *ht, const void *key, const void *value)
{
	t_ht_e	*entry;

	if (!(entry = (t_ht_e*)malloc(sizeof(t_ht_e))))
		return (NULL);
	if (!(entry->key = (void*)malloc(ht->key_size)))
		return (NULL);
	if (!(entry->value = (void*)malloc(ht->value_size)))
		return (NULL);
	ft_memcpy(entry->key, key, ((t_ht*)ht)->key_size);
	ft_memcpy(entry->value, value, (ht->value_size));
	entry->next = NULL;
	return (entry);
}

void			ft_ht_set(t_ht *ht, const void *key, const void *value)
{
	unsigned int	pos;
	t_ht_e			*cur;
	t_ht_e			*prev;

	pos = ht->hash_func(ht, key);
	cur = ht->entries[pos];
	if (cur == NULL)
	{
		ht->entries[pos] = ft_ht_make_entry(ht, key, value);
		return ;
	}
	while (cur)
	{
		if (ft_memcmp(cur->key, key, ht->key_size) == 0)
		{
			free(cur->value);
			if (!(cur->value = (char*)malloc(ht->value_size)))
				return ;
			ft_memcpy(cur->value, value, ht->value_size);
			return ;
		}
		prev = cur;
		cur = prev->next;
	}
	prev->next = ft_ht_make_entry(ht, key, value);
}
