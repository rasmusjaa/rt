/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:59:56 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/31 17:50:23 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ft_printf.h"
#include "events.h"
#include "mlx.h"
#include "thread_pool.h"
#include "mlx_image.h"
#include "debug.h"

void	reload_scene(t_rt *rt)
{
	t_scene *scene;
	char	*file;
	int		width;
	int		height;

	scene = rt->scenes[rt->cur_scene];
	file = scene->scene_config.filepath;
	width = scene->scene_config.width;
	height = scene->scene_config.height;
	ft_printf("old width %d height %d\n", width, height);
	destroy_scene(rt, scene);
	rt->scenes[rt->cur_scene] = read_scene(rt, file);
	rt->scenes[rt->cur_scene]->scene_config.width = width;
	rt->scenes[rt->cur_scene]->scene_config.height = height;
	ft_printf("old width %d height %d\n", rt->scenes[rt->cur_scene]->scene_config.width, rt->scenes[rt->cur_scene]->scene_config.height);
	rt->render_requested = TRUE;
}



int		main(int ac, char **av)
{
	t_rt	*rt;
	int		i;

	rt = rt_init(ac - 1);
	i = 0;
	if (ac == 1)
		exit_message("Usage: RTFM!");
	init_mlx(rt);
	while (i < ac - 1)
	{
		rt->scenes[i] = read_scene(rt, av[i + 1]);
		print_scene_info(rt->scenes[i]);
		i++;
	}
	create_mlx_window(rt, rt->scenes[rt->cur_scene]->scene_config.width,
		rt->scenes[rt->cur_scene]->scene_config.height, "RT");
	init_events(rt);
	mlx_loop(rt->mlx->mlx_ptr);
	return (0);
}
