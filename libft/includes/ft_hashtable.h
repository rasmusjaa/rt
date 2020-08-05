/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 12:28:44 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/05 08:54:31 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASHTABLE_H
# define FT_HASHTABLE_H

# include <stdlib.h>

typedef size_t		(*t_hash_func)(const void *ht, const void *ptr);

typedef struct		s_ht_e
{
	void			*key;
	void			*value;
	struct s_ht_e	*next;
}					t_ht_e;

/*
** typedef t_ht_e		*(*t_pair_func)(const void *ht, const void *key,\
** 	const void *value);
*/

typedef struct		s_ht
{
	t_ht_e			**entries;
	size_t			size;
	t_hash_func		hash_func;
	size_t			key_size;
	size_t			value_size;
}					t_ht;

t_ht				*ft_ht_create(size_t size, t_hash_func hash_func,\
	size_t k_size, size_t v_size);
void				ft_ht_destroy(t_ht *ht);
void				ft_ht_set(t_ht *ht, const void *key, const void *value);
void				*ft_ht_get(t_ht *ht, const void *key);
void				ft_ht_del(t_ht *ht, const void *key);

void				ft_ht_print_kv_int(t_ht_e *e);
void				ft_ht_print_kv_str(t_ht_e *e);
void				ft_ht_print(t_ht *ht, void (*print_kv)(t_ht_e*));

size_t				ft_ht_hash_str(const void *htptr, const void *keyptr);
size_t				ft_ht_hash_int(const void *htptr, const void *keyptr);

#endif
