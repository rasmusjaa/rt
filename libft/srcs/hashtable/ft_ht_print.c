/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ht_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 11:15:21 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/02 18:08:03 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtable.h"
#include "ft_printf.h"

void	ft_ht_print_kv_int(t_ht_e *e)
{
	ft_printf("%d:%d ", *(int*)(e->key), *(int*)(e->value));
}

void	ft_ht_print_kv_str(t_ht_e *e)
{
	ft_printf("%s:%s ", (char*)(e->key), (char*)(e->value));
}

void	ft_ht_print(t_ht *ht, void (*print_kv)(t_ht_e *))
{
	unsigned int	i;
	t_ht_e			*entry;

	i = 0;
	while (i < ht->size)
	{
		entry = ht->entries[i];
		if (entry == NULL)
		{
			i++;
			continue;
		}
		ft_printf("[%3d]: ", i);
		while (1)
		{
			print_kv(entry);
			if (entry->next == NULL)
				break ;
			entry = entry->next;
		}
		ft_printf("\n");
		i++;
	}
}
