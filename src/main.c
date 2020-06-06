/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:59:56 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/06 09:29:01 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_rt	*init_rt(size_t num_scenes)
{
	t_rt	*rt;

	if (!(rt = (t_rt*)malloc(sizeof(t_rt))))
		exit_message("Failed to malloc rt!");
	if (!(rt->scenes = (t_scene**)malloc(sizeof(t_scene*) * num_scenes)))
		exit_message("Failed to malloc rt->scenes!");
	rt->num_scenes = num_scenes;
	return (rt);
}

int		main(int ac, char **av)
{
	t_rt	*rt;
	int		i;

	rt = init_rt(ac);
	i = 0;
	if (ac == 1)
		exit_message("Usage:");
	else
	{
		while (i < ac - 1)
		{
			rt->scenes[i] = read_scene(av[i + 1]);
			i++;
		}
	}

	return (0);
}
