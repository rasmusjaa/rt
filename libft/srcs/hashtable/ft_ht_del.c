/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ht_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 11:14:03 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/02 18:16:53 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtable.h"
#include "libft.h"

void			ft_ht_del(t_ht *ht, const void *key)
{
	int		i;
	size_t	pos;
	t_ht_e	*cur;
	t_ht_e	*prev;

	pos = (*ht->hash_func)(ht, key);
	cur = ht->entries[pos];
	if (!cur)
		return ;
	i = 0;
	while (cur)
	{
		if (ft_memcmp(cur->key, key, ht->key_size) == 0)
		{
			if (i == 0 && !cur->next)
				ht->entries[pos] = NULL;
			if (i == 0 && cur->next)
				ht->entries[pos] = cur->next;
			if (i != 0 && !cur->next)
				prev->next = NULL;
			if (i != 0 && cur->next)
				prev->next = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
		}
		prev = cur;
		cur = prev->next;
		i++;
	}
}
