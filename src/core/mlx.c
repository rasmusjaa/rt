/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:38:27 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 16:43:17 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "mlx.h"

void	init_mlx(t_rt *rt)
{
	if (!(rt->mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		exit_message("Failed to malloc mlx!");
	rt->mlx->mlx_ptr = mlx_init();
}

void	create_mlx_window(t_rt *rt, int w, int h, char *title)
{
	if (!(rt->mlx->win_ptr = mlx_new_window(rt->mlx->mlx_ptr, w, h, title)))
		exit_message("create_mlx_window: failed to create mlx window!");
	mlx_string_put(rt->mlx->mlx_ptr, rt->mlx->win_ptr, 20, 20, 0xffffff,
		"Press space to load scene");
	mlx_string_put(rt->mlx->mlx_ptr, rt->mlx->win_ptr, 20, 40, 0xffffff,
		"Arrow keys and numpad +- to move camera");
	mlx_string_put(rt->mlx->mlx_ptr, rt->mlx->win_ptr, 20, 60, 0xffffff,
		"Numpad 2468 to rotate camera");
	mlx_string_put(rt->mlx->mlx_ptr, rt->mlx->win_ptr, 20, 80, 0xffffff,
		"C to change camera");
	mlx_string_put(rt->mlx->mlx_ptr, rt->mlx->win_ptr, 20, 100, 0xffffff,
		"S to switch scene");
	mlx_string_put(rt->mlx->mlx_ptr, rt->mlx->win_ptr, 20, 120, 0xffffff,
		"X to colorize scene");
	mlx_string_put(rt->mlx->mlx_ptr, rt->mlx->win_ptr, 20, 140, 0xffffff,
		"ESC to exit");
}
