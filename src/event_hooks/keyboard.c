/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 15:06:46 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/09 15:07:04 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	key_press_hook(int key, t_rt *rt)
{
	ft_printf("scene %d, press key %d\n", rt->cur_scene, key);
	return (0);
}

int	key_release_hook(int key, t_rt *rt)
{
	ft_printf("scene %d, release key %d\n", rt->cur_scene, key);
	return (0);
}
