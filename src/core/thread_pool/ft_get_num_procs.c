/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_num_procs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:11:35 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/23 14:11:37 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_get_num_procs(void)
{
	return (size_t)sysconf(_SC_NPROCESSORS_ONLN);
}
