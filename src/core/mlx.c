/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:38:27 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/31 17:45:16 by wkorande         ###   ########.fr       */
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
}
