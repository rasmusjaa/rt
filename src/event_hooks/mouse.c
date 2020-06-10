/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 15:05:29 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/09 15:05:58 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	mouse_press_hook(int button, int x, int y, t_rt *rt)
{
	ft_printf("scene %d, press button %d, x %d, y %d\n", rt->cur_scene, button, x, y);
	return (0);
}

int	mouse_release_hook(int button, int x, int y, t_rt *rt)
{
	ft_printf("scene %d, release button %d, x %d, y %d\n", rt->cur_scene, button, x, y);
	return (0);
}

int	mouse_move_hook(int x, int y, t_rt *rt)
{
	if (x == 0)
		ft_printf("mouse at x 0, scene %d, x %d, y %d\n", rt->cur_scene, x, y);
	return (0);
}
